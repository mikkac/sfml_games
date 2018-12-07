#include "bullet.h"
#include "game.h"
#include "pickup.h"
#include "player.h"
#include "screen.h"
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
    Texture texture_background{holder.get_texture("res/graphics/background_sheet.png")};
    IntRect arena{0, 0, 1000, 1000};
    Player player;
    Weapon weapon{24, 6, 3.f};
    Horde horde;

    std::vector<Pickup*> pickups;
    pickups.push_back(new HealthPickup(arena));
    pickups.push_back(new AmmoPickup(arena));

    int score{};
    int high_score{};

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

                unsigned num_zombies = 20;
                horde.create_horde(num_zombies, arena);

                player.spawn(resolution, arena, tile_size);
                clock.restart();
            }
        } // end LEVEL_UP

        // Update the frame
        if (game.play()) game.update(clock, screen, player, horde, weapon, pickups);

        // Draw the scene
        if (game.play()) {
            screen.window.clear();
            screen.window.setView(screen.main_view);
            screen.window.draw(background, &texture_background);
            for (auto& zombie : horde.zombies)
                if (zombie) screen.window.draw(zombie->get_sprite());

            for (auto& pickup : pickups)
                if (pickup->is_spawned()) screen.window.draw(pickup->get_sprite());

            for (auto& bullet : weapon.bullets)
                if (bullet.is_flying()) screen.window.draw(bullet.get_shape());

            screen.window.draw(player.get_sprite());
            screen.window.draw(screen.crosshair);
        }

        if (game.level_up()) {}
        if (game.pause()) {}
        if (game.game_over()) {}
        screen.window.display();
    };
    return 0;
}
