#pragma once
#include <SFML/Graphics.hpp>

namespace game
{
using namespace sf;

class Particle
{
  public:
    Particle(Vector2f velocity) : velocity_{velocity} {}
    void update(float dt_as_seconds) { position_ += velocity_ * dt_as_seconds; }

    void set_position(const Vector2f& position) { position_ = position; }
    Vector2f get_position() const { return position_; }

  private:
    Vector2f position_{};
    Vector2f velocity_;
};

} // namespace game

