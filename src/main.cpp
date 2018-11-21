#include "player.h"
#include "utils.h"
using namespace game;

using namespace sf;

int main() {
    State state{State::GAME_OVER};

    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "Mad Dead", Style::Fullscreen);
    View view_main(FloatRect(0, 0, resolution.x, resolution.y));

    Clock clock;
    Time game_time_total;

    Vector2f mouse_world_pos;
    Vector2i mouse_screen_pos;

    Player player;

    IntRect arena;

    // view_main.setCenter(player.get_center());
    while (window.isOpen()) // Game loop
    {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Return && state == State::PLAY) {
                    state = State::PAUSE;
                } else if (event.key.code == Keyboard::Return && state == State::GAME_OVER) {
                    state = State::LEVEL_UP;
                } else if (event.key.code == Keyboard::Return && state == State::PAUSE) {
                    state = State::PLAY;
                    clock.restart();
                }

                if (state == State::PLAY) {}
            }
        } // end event polling

        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

        // Handle WSAD
        if (state == State::PLAY) {
            player.move_up(Keyboard::isKeyPressed(Keyboard::W));
            player.move_down(Keyboard::isKeyPressed(Keyboard::S));
            player.move_left(Keyboard::isKeyPressed(Keyboard::A));
            player.move_right(Keyboard::isKeyPressed(Keyboard::D));
        }

        // Handle LEVEL_UP state
        if (state == State::LEVEL_UP) {
            if (event.key.code == Keyboard::Num1) state = State::PLAY;
            if (event.key.code == Keyboard::Num2) state = State::PLAY;
            if (event.key.code == Keyboard::Num3) state = State::PLAY;
            if (event.key.code == Keyboard::Num4) state = State::PLAY;
            if (event.key.code == Keyboard::Num5) state = State::PLAY;
            if (event.key.code == Keyboard::Num6) state = State::PLAY;

            if (state == State::PLAY) {
                // Preapre the level
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;

                int tile_size{50};

                player.spawn(resolution, arena, tile_size);
                clock.restart();
            }
        } // end LEVEL_UP

        // Update the frame
        if (state == State::PLAY) {
            Time dt = clock.restart();
            game_time_total += dt;
            float dt_as_seconds = dt.asSeconds();
            mouse_screen_pos = Mouse::getPosition();

            // Convert mouse postition to world coords
            mouse_world_pos = window.mapPixelToCoords(mouse_screen_pos, view_main);

            player.update(dt_as_seconds, mouse_screen_pos);
            Vector2f player_pos(player.get_center());
            view_main.setCenter(player.get_center());
        } // end updating the frame

        // Draw the scene
        if (state == State::PLAY) {
            window.clear();
            window.setView(view_main);
            window.draw(player.get_sprite());
        }

        if (state == State::LEVEL_UP) {}
        if (state == State::PAUSE) {}
        if (state == State::GAME_OVER) {}
        window.display();
    }
    return 0;
}
