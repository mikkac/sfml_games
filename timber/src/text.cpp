#include "text.h"
namespace timber
{
Text::Text(sf::RenderWindow& window, const std::string& text, sf::Font& font, int charSize,
           sf::Color color)
    : mWindow{window}
{
    mText.setFont(font);
    mText.setString(text);
    mText.setCharacterSize(charSize);
    mText.setFillColor(color);
}

void Text::setPosition(vec2 position)
{
    mText.setPosition(position.x, position.y);
}

void Text::setString(const std::string& text)
{
    mText.setString(text);
}

void Text::draw()
{
    mWindow.draw(mText);
}

void Text::center()
{
    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
}

}  // namespace timber