#pragma once
#include <SFML/Graphics.hpp>

namespace game
{
using namespace sf;

struct Motion {
    float jump_duration{};
    float time_of_jump{};
    bool just_jumped{false};
    bool is_jumping{false};
    bool is_falling{false};
    bool left{false};
    bool right{false};

    float gravity{};
    float speed{400.f};
};

struct Body {
    FloatRect feet, head, left, right;
};

class PlayableCharacter
{
  public:
    void spawn(const Vector2f& start_pos, float gravity);
    void update(float elapsed_time);

    virtual bool handle_input() = 0;

    // Control character's motion
    void stop_jump();
    void stop_falling(float position);
    void stop_right(float position);
    void stop_left(float position);

    // Get body values
    FloatRect get_feet() const { return body_.feet; }
    FloatRect get_head() const { return body_.head; }
    FloatRect get_left() const { return body_.left; }
    FloatRect get_right() const { return body_.right; }

    Vector2f get_center() const;
    FloatRect get_position() const { return sprite_.getGlobalBounds(); }
    Sprite get_sprite() const { return sprite_; }

  private:
    void update_motion(float elapsed_time);
    void update_body(const FloatRect& position);

  protected:
    Sprite sprite_;
    Motion motion_;

  private:
    Vector2f position_;
    Body body_;
    Texture texture_;
};
} // namespace game
