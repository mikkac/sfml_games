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

    viewMain.setCenter(player.getCenter());
    window.setView(viewMain);
    while (window.isOpen())  // Game loop
    {
        viewMain.rotate(180);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        window.clear();
        window.draw(player.getSprite());
        window.display();
    }
    return 0;
}
