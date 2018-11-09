#include "text.h"
namespace timber
{
Text::Text(sf::RenderWindow& window, const char* text, sf::Font& font, int charSize,
           sf::Color color)
    : mWindow{window}
{
    mText.setFont(font);
    mText.setString(text);
    mText.setCharacterSize(charSize);
    mText.setFillColor(color);
}
void Text::setString(const char* text)
{
    mText.setString(text);
}
void Text::setPosition(vec2 position)
{
    mText.setPosition(position.x, position.y);
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