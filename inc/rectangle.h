#pragma once
#include "utils.h"
namespace timber
{
class Rectangle
{
public:
    Rectangle(sf::RenderWindow& window, vec2 size, vec2 position, sf::Color color);
    void setSize(vec2 size);
    void setColor(sf::Color color);
    void resetSize();
    void draw();

private:
    vec2 mStartSize;
    sf::RenderWindow& mWindow;
    sf::RectangleShape mShape;
};

void updateTimeBarColor(Rectangle& timeBar, float timePrecentage);

}  // namespace timber