#include "bullet.h"
#include "game.h"
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
    IntRect arena;
    Player player;

    unsigned num_zombies{};
    unsigned num_zombies_alive{};
    std::vector<Zombie*> zombies;

    Bullet bullets[5];
    int current_bullet{0};
    int bullets_spare{24};
    int bullets_in_clip{6};
    int clip_size{6};
    float fire_rate{3.f};
    Time last_pressed{Time::Zero};

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
                    if (event.key.code == Keyboard::R) {
                        if (bullets_spare >= clip_size) {
                            bullets_in_clip = clip_size;
                            bullets_spare -= clip_size;
                        } else if (bullets_spare > 0) {
                            bullets_in_clip = bullets_spare;
                            bullets_spare = 0;
                        } else {
                            // More here soon
                        }
                    }
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
                if (game.get_time_total().asMilliseconds() - last_pressed.asMilliseconds() >
                        1000.f / fire_rate &&
                    bullets_in_clip > 0) {
                    bullets[current_bullet].shoot(player.get_center(), game.get_mouse_world_pos());
                    if (++current_bullet > 4) current_bullet = 0;
                    last_pressed = game.get_time_total();
                    --bullets_in_clip;
                }
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
                arena.width = 1000;
                arena.height = 1000;
                arena.left = 0;
                arena.top = 0;
                int tile_size{create_background(background, arena)};

                num_zombies = 20;
                for (auto& zombie : zombies) delete zombie;
                zombies = create_horde(num_zombies, arena);
                num_zombies_alive = num_zombies;

                player.spawn(resolution, arena, tile_size);
                clock.restart();
            }
        } // end LEVEL_UP

        // Update the frame
        if (game.play()) game.update(clock, screen, player, zombies, bullets);

        // Draw the scene
        if (game.play()) {
            screen.window.clear();
            screen.window.setView(screen.main_view);
            screen.window.draw(background, &texture_background);
            for (auto& zombie : zombies) screen.window.draw(zombie->get_sprite());
            for (unsigned idx = 0; idx < 5; ++idx)
                if (bullets[idx].is_flying()) screen.window.draw(bullets[idx].get_shape());

            screen.window.draw(player.get_sprite());
            screen.window.draw(screen.crosshair);
        }

        if (game.level_up()) {}
        if (game.pause()) {}
        if (game.game_over()) {}
        screen.window.display();
    }
    for (auto& zombie : zombies) delete zombie;
    return 0;
}
