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
    Game game{};
    Clock clock;
    TextureHolder holder;
    VertexArray background;
    IntRect arena;
    Player player;

    unsigned num_zombies{};
    unsigned num_zombies_alive{};
    std::vector<Zombie*> zombies;

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

                if (game.play()) {}
            }
        } // end event polling

        if (Keyboard::isKeyPressed(Keyboard::Escape)) screen.window.close();

        // Handle WSAD
        if (game.play()) {
            player.move_up(Keyboard::isKeyPressed(Keyboard::W));
            player.move_down(Keyboard::isKeyPressed(Keyboard::S));
            player.move_left(Keyboard::isKeyPressed(Keyboard::A));
            player.move_right(Keyboard::isKeyPressed(Keyboard::D));
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
                arena.width = 1280;
                arena.height = 1280;
                arena.left = 0;
                arena.top = 0;
                int tile_size{create_background(background, arena)};

                num_zombies = 1000;
                for (auto& zombie : zombies) delete zombie;
                zombies = create_horde(num_zombies, arena);
                num_zombies_alive = num_zombies;

                player.spawn(resolution, arena, tile_size);
                clock.restart();
            }
        } // end LEVEL_UP

        // Update the frame
        if (game.play()) game.update(clock, screen, player, zombies);

        // Draw the scene
        if (game.play()) {
            screen.window.clear();
            screen.window.setView(screen.main_view);
            screen.window.draw(background, &texture_background);
            for (auto& zombie : zombies) screen.window.draw(zombie->get_sprite());
            screen.window.draw(player.get_sprite());
        }

        if (game.level_up()) {}
        if (game.pause()) {}
        if (game.game_over()) {}
        screen.window.display();
    }
    for (auto& zombie : zombies) delete zombie;
    return 0;
}
