#pragma once
#include <SFML/Graphics.hpp>
namespace game
{
using namespace sf;

class Bullet
{
  public:
    Bullet() { shape_.setRadius(2.5f); }
    void stop() { flying_ = false; };
    void shoot(const Vector2f& start_pos, const Vector2f& target_pos);
    void update(float elapsed_time);
    bool is_flying() const { return flying_; }
    FloatRect get_position() const { return shape_.getGlobalBounds(); }
    CircleShape get_shape() const { return shape_; }

  private:
    Vector2f position_{};
    CircleShape shape_;
    bool flying_{false};
    float speed_{3000.f}; // pixels per second
    Vector2f distance_{}; // pixels per frame
    Vector2f min_{};
    Vector2f max_{};
};
} // namespace game