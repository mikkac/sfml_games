#include "bullet.h"
#include "game.h"
#include "hud.h"
#include "pickup.h"
#include "player.h"
#include "rectangle.h"
#include "screen.h"
#include "sounds.h"
#include "text_wrapper.h"
#include "texture_holder.h"
#include "utils.h"
#include "zombie.h"
#include "zombie_arena.h"
#include <SFML/Audio.hpp>
using namespace game;

using namespace sf;

int main() {
    Vector2u resolution{VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height};

    Screen screen{resolution, "Mad Dead"};
    screen.window.setMouseCursorVisible(false); // Hide the mouse pointer
    Game game{};
    Hud hud{};
    Clock clock;
    Score::get_instance().load_high_score();

    VertexArray background;
    IntRect arena{0, 0, 500, 500};
    Player player;
    Weapon weapon{24, 6, 3.f};
    Horde horde;

    std::array<Pickup*, 2> pickups;
    pickups[0] = new HealthPickup(arena);
    pickups[1] = new AmmoPickup(arena);

    SoundBuffer buffer;
    buffer.loadFromFile("res/sound/hit.wav");
    Sound sound_hit{buffer};

    while (screen.window.isOpen()) // Game loop
    {
        Event event;
        while (screen.window.pollEvent(event)) {
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Return && game.play()) {
                    game.set_state(State::PAUSE);
                } else if (event.key.code == Keyboard::Return && game.game_over()) {
                    game.set_state(State::LEVEL_UP);
                    Score::get_instance().reset();
                    weapon.reset();
                    player.reset();
                } else if (event.key.code == Keyboard::Return && game.pause()) {
                    game.set_state(State::PLAY);
                    clock.restart();
                }

                if (game.play()) {
                    // Reloading
                    if (event.key.code == Keyboard::R) {
                        if (weapon.reload()) {
                            Sounds::get_instance().get_sound(AudioType::RELOAD).play();
                        } else {
                            Sounds::get_instance().get_sound(AudioType::RELOAD_FAILED).play();
                        }
                    }
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
                weapon.shoot(player.get_center(), game.get_mouse_world_pos(), game.get_time_total());
                // Sounds::get_instance().get_sound(AudioType::SHOOT).play();
            }
        }

        // Handle LEVEL_UP state
        if (game.level_up()) {
            if (event.key.code == Keyboard::Num1) {
                weapon.increment_fire_rate();
                game.set_state(State::PLAY);
            }
            if (event.key.code == Keyboard::Num2) {
                weapon.double_clip_size();
                game.set_state(State::PLAY);
            }
            if (event.key.code == Keyboard::Num3) {
                player.upgrade_health();
                game.set_state(State::PLAY);
            }
            if (event.key.code == Keyboard::Num4) {
                player.upgrade_speed();
                game.set_state(State::PLAY);
            }
            if (event.key.code == Keyboard::Num5) {
                pickups[0]->upgrade(PickupType::AMMO);
                game.set_state(State::PLAY);
            }
            if (event.key.code == Keyboard::Num6) {
                pickups[1]->upgrade(PickupType::HEALTH);
                game.set_state(State::PLAY);
            }

            if (game.play()) {
                // Preapre the level
                arena.width = 500 + 500 * horde.wave_number;
                arena.height = 500 + 500 * horde.wave_number;
                int tile_size{create_background(background, arena)};

                unsigned num_zombies = 4 + 4 * horde.wave_number;
                horde.create_horde(num_zombies, arena);

                player.spawn(resolution, arena, tile_size);
                clock.restart();

                Sounds::get_instance().get_sound(AudioType::POWERUP).play();
            }
        } // end LEVEL_UP

        // Update the frame
        if (game.play()) {
            game.update(clock, screen, player, horde, weapon, pickups);
            hud.update(player, weapon, horde);
        }

        // Draw the scene
        if (game.play()) {
            screen.window.clear();
            screen.set_main_view();
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

            screen.set_hud_view();
            screen.window.draw(hud.content.sprite_ammo_icon);
            screen.window.draw(hud.content.text_ammo.get_text());
            screen.window.draw(hud.content.text_score.get_text());
            screen.window.draw(hud.content.text_high_score.get_text());
            screen.window.draw(hud.content.health_bar.get_shape());
            screen.window.draw(hud.content.text_wave_number.get_text());
            screen.window.draw(hud.content.text_zombies_remaining.get_text());
        }

        if (game.level_up()) {
            screen.window.draw(hud.content.sprite_game_over);
            screen.window.draw(hud.content.text_level_up.get_text());
        }
        if (game.pause()) { screen.window.draw(hud.content.text_paused.get_text()); }
        if (game.game_over()) {
            screen.window.draw(hud.content.sprite_game_over);
            screen.window.draw(hud.content.text_game_over.get_text());
            screen.window.draw(hud.content.text_score.get_text());
            screen.window.draw(hud.content.text_high_score.get_text());
        }
        screen.window.display();
    }
    for (auto& pickup : pickups) {
        if (pickup) {
            delete pickup;
            pickup = nullptr;
        }
    }
    return 0;
}
