#pragma once
#include <SFML/Graphics.hpp>
#include <array>

namespace game
{
using namespace sf;

const unsigned kBulletsArraySize{5};
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

class Weapon
{
    using Bullets = std::array<Bullet, kBulletsArraySize>;
    const int kStartBulletsSpare{24};
    const int kStartBulletsInClip{6};
    const int kStartClipSize{6};
    const float kStartFireRate{3.f};

  public:
    Weapon(int bullets_spare, int clip_size, float fire_rate) : bullets_spare{bullets_spare}, clip_size{clip_size}, fire_rate{fire_rate} {}
    bool reload();
    void reset();
    void shoot(const Vector2f& start_pos, const Vector2f& target_pos, Time game_total_time);
    void increment_fire_rate() { ++fire_rate; }
    void double_clip_size() { clip_size += clip_size; }

  public:
    Bullets bullets; // too many external functions need access to bullets to make it private
    int current_bullet{0};
    int bullets_spare{kStartBulletsSpare};
    int bullets_in_clip{kStartBulletsInClip};
    int clip_size{kStartClipSize};
    float fire_rate{kStartFireRate};
    Time last_pressed{Time::Zero};
};
} // namespace game
