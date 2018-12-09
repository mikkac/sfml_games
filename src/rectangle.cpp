#include "rectangle.h"
namespace timber
{
Rectangle::Rectangle(const Vector2f& size, const Vector2f& position, Color color)
    : start_size_{size} {
    shape_.setSize(Vector2f{start_size_.x, start_size_.y});
    shape_.setPosition(position.x, position.y);
    shape_.setFillColor(color);
}

void Rectangle::set_size(const Vector2f& size) {
    shape_.setSize(Vector2f{size.x, size.y});
}

void Rectangle::set_color(Color color) {
    shape_.setFillColor(color);
}

void Rectangle::reset_size() {
    set_size(start_size_);
}

} // namespace timber