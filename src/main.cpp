#include "utils.h"

using namespace game;

int main()
{
    // Create window
    sf::VideoMode vm(1920, 1080);
    sf::RenderWindow window(vm, "Mad Dead", sf::Style::Fullscreen);

    while (window.isOpen())  // Game loop
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        window.clear();
        window.display();
    }
    return 0;
}
