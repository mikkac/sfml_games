#include "rectangle.h"
namespace timber
{
Rectangle::Rectangle(sf::RenderWindow& window, vec2 size, vec2 position, sf::Color color)
    : mWindow{window}, mStartSize{size}
{
    mShape.setSize(sf::Vector2f{mStartSize.x, mStartSize.y});
    mShape.setPosition(position.x, position.y);
    mShape.setFillColor(color);
}

void Rectangle::setSize(vec2 size)
{
    mShape.setSize(sf::Vector2f{size.x, size.y});
}

void Rectangle::setColor(sf::Color color)
{
    mShape.setFillColor(color);
}

void Rectangle::resetSize()
{
    setSize(mStartSize);
}

void Rectangle::draw()
{
    mWindow.draw(mShape);
}

void updateTimeBarColor(Rectangle& timeBar, float timePrecentage)
{
    timeBar.setColor({1 - timePrecentage * 255, timePrecentage * 255, 0});
}
}  // namespace timber