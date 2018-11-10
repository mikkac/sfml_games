#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include "utils.h"
namespace timber
{
class Text
{
public:
    Text(sf::RenderWindow& window, const std::string& text, sf::Font& font, int charSize,
         sf::Color color);
    void setPosition(vec2 position);
    void setString(const std::string& text);
    void draw();
    void center();

private:
    sf::RenderWindow& mWindow;
    sf::Text mText;
};

}  // namespace timber