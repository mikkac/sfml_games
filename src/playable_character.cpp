#include "playable_character.h"

namespace game
{
void PlayableCharacter::spawn(const Vector2f& start_pos, float gravity) {
    position_ = start_pos;
    motion_.gravity = gravity;
    sprite_.setPosition(position_);
}

void PlayableCharacter::update(float elapsed_time) {
    update_motion(elapsed_time);
    update_body(get_position());
    sprite_.setPosition(position_);
}

void PlayableCharacter::update_motion(float elapsed_time) {
    // Update position of player
    if (motion_.right) position_.x += motion_.speed * elapsed_time;
    if (motion_.left) position_.x -= motion_.speed * elapsed_time;

    if (motion_.is_jumping) {
        motion_.time_of_jump += elapsed_time;
        if (motion_.time_of_jump < motion_.jump_duration) {
            position_.y -= motion_.gravity * 2 * elapsed_time;
        } else {
            motion_.is_falling = true;
            motion_.is_jumping = false;
        }
    }

    if (motion_.is_falling) position_.y += motion_.gravity * elapsed_time;
}

void PlayableCharacter::update_body(const FloatRect& position) {
    // Update all parts of player's body
    body_.feet.left = position.left + 3;
    body_.feet.top = position.top + position.height - 1;
    body_.feet.width = position.width - 6;
    body_.feet.height = 1;

    body_.head.left = position.left;
    body_.head.top = position.top + (position.height * 0.3f);
    body_.head.width = position.width;
    body_.head.height = 1;

    body_.right.left = position.left + position.width - 2;
    body_.right.top = position.top + (position.height * 0.35f);
    body_.right.width = 1;
    body_.right.height = position.height * 0.3f;

    body_.left.left = position.left;
    body_.left.top = position.top + (position.height * 0.5f);
    body_.left.width = 1;
    body_.left.height = position.height * 0.3f;
}
} // namespace game
