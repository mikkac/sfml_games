#include "bullet.h"
#include <cmath>
namespace game
{
void Bullet::shoot(const Vector2f& start_pos, const Vector2f& target_pos) {
    if (start_pos == target_pos) return;

    flying_ = true;
    position_ = start_pos;

    float gradient{static_cast<float>(fabs((start_pos.x - target_pos.x) / (start_pos.y - target_pos.y)))};

    float ratio_xy{speed_ / (1.f + gradient)};

    distance_ = Vector2f(ratio_xy * gradient, ratio_xy);

    if (target_pos.x < start_pos.x) distance_.x *= -1.f;
    if (target_pos.y < start_pos.y) distance_.y *= -1.f;

    float range{1000.f};

    min_ = Vector2f(start_pos.x - range, start_pos.y - range);
    max_ = Vector2f(start_pos.x + range, start_pos.y + range);

    shape_.setPosition(position_);
}

void Bullet::update(float elapsed_time) {
    position_ += distance_ * elapsed_time;
    shape_.setPosition(position_);

    if (position_.x < min_.x || position_.x > max_.x || position_.y < min_.y || position_.y > max_.y) flying_ = false;
}

bool Weapon::reload() {
    if (bullets_spare >= clip_size) {
        bullets_in_clip = clip_size;
        bullets_spare -= clip_size;
        return true;
    } else if (bullets_spare > 0) {
        bullets_in_clip = bullets_spare;
        bullets_spare = 0;
        return true;
    } else {
        return false; // false when reloading failed
    }
}

void Weapon::reset() {
    current_bullet = 0;
    bullets_spare = kStartBulletsSpare;
    bullets_in_clip = kStartBulletsInClip;
    clip_size = kStartClipSize;
    fire_rate = kStartFireRate;
}

void Weapon::shoot(const Vector2f& start_pos, const Vector2f& target_pos, Time game_total_time) {
    if (game_total_time.asMilliseconds() - last_pressed.asMilliseconds() > 1000.f / fire_rate && bullets_in_clip > 0) {
        bullets[current_bullet].shoot(start_pos, target_pos);
        if (++current_bullet > kBulletsArraySize - 1) current_bullet = 0;
        last_pressed = game_total_time;
        --bullets_in_clip;
    }
}
} // namespace game
