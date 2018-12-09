#pragma once
#include "utils.h"
namespace timber
{
using namespace sf;

class Rectangle
{
  public:
    Rectangle(const Vector2f& size, const Vector2f& position, Color color);
    void set_size(const Vector2f& size);
    void set_color(sf::Color color);
    void reset_size();

  private:
    Vector2f start_size_;
    RectangleShape shape_;
};

} // namespace timber