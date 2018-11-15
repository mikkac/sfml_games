#include "player.h"
#include "utils.h"
using namespace game;

int main()
{
    State state{State::GAME_OVER};

    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Mad Dead",
                            sf::Style::Fullscreen);
    sf::View viewMain(sf::FloatRect(0, 0, resolution.x, resolution.y));

    sf::Clock clock;
    sf::Time gameTimeTotal;

    sf::Vector2f mouseWorldPosition;
    sf::Vector2i mouseScreenPosition;

    Player player;

    sf::IntRect arena;

    // viewMain.setCenter(player.getCenter());
    while (window.isOpen())  // Game loop
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Return && state == State::PLAY)
                    state = State::PAUSE;
                else if (event.key.code == sf::Keyboard::Return && state == State::GAME_OVER)
                    state = State::LEVEL_UP;
                else if (event.key.code == sf::Keyboard::Return && state == State::PAUSE)
                {
                    state = State::PLAY;
                    clock.restart();
                }

                if (state == State::PLAY)
                {
                }
            }
        }  // end event polling

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

        // Handle WSAD
        if (state == State::PLAY)
        {
            player.moveUp(sf::Keyboard::isKeyPressed(sf::Keyboard::W));
            player.moveDown(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
            player.moveLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
            player.moveRight(sf::Keyboard::isKeyPressed(sf::Keyboard::D));
        }

        // Handle LEVEL_UP state
        if (state == State::LEVEL_UP)
        {
            if (event.key.code == sf::Keyboard::Num1) state = State::PLAY;
            if (event.key.code == sf::Keyboard::Num2) state = State::PLAY;
            if (event.key.code == sf::Keyboard::Num3) state = State::PLAY;
            if (event.key.code == sf::Keyboard::Num4) state = State::PLAY;
            if (event.key.code == sf::Keyboard::Num5) state = State::PLAY;
            if (event.key.code == sf::Keyboard::Num6) state = State::PLAY;

            if (state == State::PLAY)
            {
                // Preapre the level
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;

                int tileSize{50};

                player.spawn(resolution, arena, tileSize);
                clock.restart();
            }
        }  // end LEVEL_UP

        // Update the frame
        if (state == State::PLAY)
        {
            sf::Time dt = clock.restart();
            gameTimeTotal += dt;
            float dtAsSeconds = dt.asSeconds();
            mouseScreenPosition = sf::Mouse::getPosition();

            // Convert mouse postition to world coords
            mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, viewMain);

            player.update(dtAsSeconds, mouseScreenPosition);
            sf::Vector2f playerPosition(player.getCenter());
            viewMain.setCenter(player.getCenter());
        }  // end updating the frame

        // Draw the scene
        if (state == State::PLAY)
        {
            window.clear();
            window.setView(viewMain);
            window.draw(player.getSprite());
        }

        if (state == State::LEVEL_UP)
        {
        }
        if (state == State::PAUSE)
        {
        }
        if (state == State::GAME_OVER)
        {
        }
        window.display();
    }
    return 0;
}
