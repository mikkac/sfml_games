#pragma once
#include "utils.h"

using namespace sf;

namespace game
{
class Player
{
  public:
    Player();
    void spawn(const Vector2u& resolution, const IntRect& arena, int tile_size);
    void reset();
    bool hit(Time time_hit);
    void update(float elapsed_time, Vector2i mouse_pos);

    // Boosts
    void upgrade_health();
    void upgrade_speed();
    void increase_health(int amount);

    // Move in a given direction
    void move_up(bool is_moving) { pressed_.up = is_moving; }
    void move_down(bool is_moving) { pressed_.down = is_moving; }
    void move_left(bool is_moving) { pressed_.left = is_moving; }
    void move_right(bool is_moving) { pressed_.right = is_moving; }

    // Getters
    FloatRect get_position() const { return sprite_.getGlobalBounds(); }
    Vector2f get_center() const { return position_; }
    float get_rotation() const { return sprite_.getRotation(); }
    Sprite get_sprite() const { return sprite_; }
    int get_health() const { return health_; }
    Time get_last_hit_time() const { return last_hit_time_; }

  private:
    const float kStartHealth{100.f};
    const float kStartSpeed{200.f};
    Vector2f position_;
    Sprite sprite_;
    // Texture mTexture;
    struct {
        bool up, down, left, right;
    } pressed_;

    int health_{static_cast<int>(kStartHealth)};
    int max_health_{static_cast<int>(kStartHealth)};
    float speed_{kStartSpeed}; // speed in pixels per second
    Time last_hit_time_;

    // Arena data
    struct {
        Vector2u resolution;
        IntRect arena;
        int tile_size;
    } screen_;
}; // namespace game

} // namespace game