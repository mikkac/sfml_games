#include "bullet.h"
#include "game.h"
#include "pickup.h"
#include "player.h"
#include "rectangle.h"
#include "screen.h"
#include "text_wrapper.h"
#include "texture_holder.h"
#include "utils.h"
#include "zombie.h"
#include "zombie_arena.h"

using namespace game;

using namespace sf;

int main() {
    Vector2u resolution{VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height};

    Screen screen{resolution, "Mad Dead"};
    screen.window.setMouseCursorVisible(false); // Hide the mouse pointer
    Game game{};
    Clock clock;

    VertexArray background;
    IntRect arena{0, 0, 1000, 1000};
    Player player;
    Weapon weapon{24, 6, 3.f};
    Horde horde;

    std::array<Pickup*, 2> pickups;
    pickups[0] = new HealthPickup(arena);
    pickups[1] = new AmmoPickup(arena);

    // Create HUD
    Sprite sprite_game_over{Sprite(holder.get_texture("res/graphics/background.png"))};
    sprite_game_over.setPosition(0.f, 0.f);

    View view_hud(FloatRect(0.f, 0.f, resolution.x, resolution.y));

    Sprite sprite_ammo_icon{Sprite(holder.get_texture("res/graphics/ammo_icon.png"))};
    sprite_ammo_icon.setPosition(20.f, 980.f);

    Font font;
    font.loadFromFile("res/fonts/zombiecontrol.ttf");

    TextWrapper text_paused{"Press Enter \n to continue", font, 155, Color::White};
    text_paused.set_position(Vector2f(400.f, 400.f));

    TextWrapper text_game_over{"Press Enter to play", font, 125, Color::White};
    text_game_over.set_position(Vector2f(250.f, 850.f));

    std::string level_up{
        "\n1- Increase rate of fire\
        \n2- Increase clip size (next reload)\
        \n3- Increase max health\
        \n4- Increase run speed\
        \n5- More and better health pickups\
        \n6- More and better ammo pickups"};
    TextWrapper text_level_up{level_up, font, 80, Color::White};
    text_level_up.set_position(Vector2f(150.f, 250.f));

    TextWrapper text_ammo{"", font, 55, Color::White};
    text_ammo.set_position(Vector2f(200.f, 980.f));

    TextWrapper text_score{"", font, 55, Color::White};
    text_score.set_position(Vector2f(20.f, 0.f));

    std::stringstream stream;
    stream << "High Score: " << game.get_high_score();
    TextWrapper text_high_score{stream.str(), font, 55, Color::White};
    text_high_score.set_position(Vector2f(1400.f, 0.f));

    TextWrapper text_zombies_remaining{"Zombies: 100", font, 55, Color::White};
    text_zombies_remaining.set_position(Vector2f(1500.f, 980.f));

    TextWrapper text_wave_number{"Wave: 0", font, 55, Color::White};
    text_wave_number.set_position(Vector2f(1250.f, 980.f));

    Rectangle health_bar{Vector2f(player.get_health() * 3.f, 50.f), Vector2f(450.f, 980.f),
                         Color::Red};

    unsigned frames_since_last_hud_update{};
    unsigned fps_measurement_frame_interval{1000};

    while (screen.window.isOpen()) // Game loop
    {
        Event event;
        while (screen.window.pollEvent(event)) {
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Return && game.play()) {
                    game.set_state(State::PAUSE);
                } else if (event.key.code == Keyboard::Return && game.game_over()) {
                    game.set_state(State::LEVEL_UP);
                } else if (event.key.code == Keyboard::Return && game.pause()) {
                    game.set_state(State::PLAY);
                    clock.restart();
                }

                if (game.play()) {
                    // Reloading
                    if (event.key.code == Keyboard::R) { weapon.reload(); }
                }
            } else {
                continue;
            }
        } // end event polling

        if (Keyboard::isKeyPressed(Keyboard::Escape)) screen.window.close();

        // Handle WSAD
        if (game.play()) {
            player.move_up(Keyboard::isKeyPressed(Keyboard::W));
            player.move_down(Keyboard::isKeyPressed(Keyboard::S));
            player.move_left(Keyboard::isKeyPressed(Keyboard::A));
            player.move_right(Keyboard::isKeyPressed(Keyboard::D));

            if (Mouse::isButtonPressed(Mouse::Left)) {
                weapon.shoot(player.get_center(), game.get_mouse_world_pos(),
                             game.get_time_total());
            }
        }

        // Handle LEVEL_UP state
        if (game.level_up()) {
            if (event.key.code == Keyboard::Num1) game.set_state(State::PLAY);
            if (event.key.code == Keyboard::Num2) game.set_state(State::PLAY);
            if (event.key.code == Keyboard::Num3) game.set_state(State::PLAY);
            if (event.key.code == Keyboard::Num4) game.set_state(State::PLAY);
            if (event.key.code == Keyboard::Num5) game.set_state(State::PLAY);
            if (event.key.code == Keyboard::Num6) game.set_state(State::PLAY);

            if (game.play()) {
                // Preapre the level
                int tile_size{create_background(background, arena)};

                unsigned num_zombies = 2;
                horde.create_horde(num_zombies, arena);

                player.spawn(resolution, arena, tile_size);
                clock.restart();
            }
        } // end LEVEL_UP

        // Update the frame
        if (game.play()) {
            game.update(clock, screen, player, horde, weapon, pickups);
            health_bar.set_size(Vector2f(player.get_health() * 3.f, 50.f));
            ++frames_since_last_hud_update;
            if (frames_since_last_hud_update > fps_measurement_frame_interval) {
                std::stringstream stream_ammo;
                std::stringstream stream_score;
                std::stringstream stream_high_score;
                std::stringstream stream_wave;
                std::stringstream stream_zombies_alive;

                stream_ammo << weapon.bullets_in_clip << "/" << weapon.bullets_spare;
                text_ammo.set_string(stream_ammo.str());

                stream_score << "Score: " << game.get_score();
                text_score.set_string(stream_score.str());

                stream_high_score << "High score: " << game.get_high_score();
                text_high_score.set_string(stream_high_score.str());

                stream_wave << "Wave: " << horde.wave_number;
                text_wave_number.set_string(stream_wave.str());

                stream_zombies_alive << "Zombies: " << horde.num_zombies_alive;
                text_zombies_remaining.set_string(stream_zombies_alive.str());

                frames_since_last_hud_update = 0;
            }
        }
        // Draw the scene
        if (game.play()) {
            screen.window.clear();
            screen.window.setView(screen.main_view);
            screen.window.draw(background, &texture_background);

            // first draw blood stains to avoid invalid overlaping of textures
            for (auto& zombie : horde.zombies)
                if (zombie && not zombie->is_alive()) screen.window.draw(zombie->get_sprite());
            // then draw alive zombies
            for (auto& zombie : horde.zombies)
                if (zombie && zombie->is_alive()) screen.window.draw(zombie->get_sprite());

            for (auto& pickup : pickups)
                if (pickup->is_spawned()) screen.window.draw(pickup->get_sprite());

            for (auto& bullet : weapon.bullets)
                if (bullet.is_flying()) screen.window.draw(bullet.get_shape());

            screen.window.draw(player.get_sprite());
            screen.window.draw(screen.crosshair);

            screen.window.setView(view_hud);
            screen.window.draw(sprite_ammo_icon);
            screen.window.draw(text_ammo.get_text());
            screen.window.draw(text_score.get_text());
            screen.window.draw(text_high_score.get_text());
            screen.window.draw(health_bar.get_shape());
            screen.window.draw(text_wave_number.get_text());
            screen.window.draw(text_zombies_remaining.get_text());
        }

        if (game.level_up()) {
            screen.window.draw(sprite_game_over);
            screen.window.draw(text_level_up.get_text());
        }
        if (game.pause()) { screen.window.draw(text_paused.get_text()); }
        if (game.game_over()) {
            screen.window.draw(sprite_game_over);
            screen.window.draw(text_game_over.get_text());
            screen.window.draw(text_score.get_text());
            screen.window.draw(text_high_score.get_text());
        }
        screen.window.display();
    };
    for (auto& pickup : pickups) {
        if (pickup) {
            delete pickup;
            pickup = nullptr;
        }
    }
    return 0;
}
