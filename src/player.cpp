#include "player.h"
#include <cmath>

using namespace sf;

namespace game
{
Player::Player() {
    sprite_.setTexture(texture_player);
    sprite_.setOrigin(25, 25);
}

void Player::spawn(const Vector2u& resolution, const IntRect& arena, int tile_size) {
    position_.x = arena.width / 2.f;
    position_.y = arena.height / 2.f;
    screen_.resolution = resolution;
    screen_.arena = arena;
    screen_.tile_size = tile_size;
}

void Player::reset() {
    health_ = static_cast<int>(kStartHealth);
    max_health_ = static_cast<int>(kStartHealth);
    speed_ = kStartSpeed;
}

bool Player::hit(Time time_hit) {
    if (time_hit.asMilliseconds() - last_hit_time_.asMilliseconds() > 200) {
        last_hit_time_ = time_hit;
        health_ -= 10;
        return true;
    } else
        return false;
}

void Player::update(float elapsed_time, Vector2i mouse_pos) {
    float shift = elapsed_time * speed_;
    if (pressed_.up) position_.y -= shift;
    if (pressed_.down) position_.y += shift;
    if (pressed_.left) position_.x -= shift;
    if (pressed_.right) position_.x += shift;

    sprite_.setPosition(position_);

    // Keep the player in the area
    if (auto bound = screen_.arena.width - screen_.tile_size; position_.x > bound)
        position_.x = bound;

    if (auto bound = screen_.arena.left + screen_.tile_size; position_.x < bound)
        position_.x = bound;

    if (auto bound = screen_.arena.height - screen_.tile_size; position_.y > bound)
        position_.x = bound;

    if (auto bound = screen_.arena.top + screen_.tile_size; position_.x < bound)
        position_.x = bound;

    // Calculate the angle the player is facing
    float angle =
        (atan2(mouse_pos.y - screen_.resolution.y / 2.f, mouse_pos.x - screen_.resolution.x / 2.f) *
         180.0) /
        3.1415;

    sprite_.setRotation(angle);
}

// Boosts -------------------------------------------------
void Player::upgrade_health() {
    health_ += static_cast<int>(kStartHealth * 0.2f);
}

void Player::upgrade_speed() {
    speed_ += static_cast<int>(kStartSpeed * 0.2f);
}

void Player::increase_health(int amount) {
    health_ += amount;
    if (health_ > max_health_) health_ = max_health_;
}

} // namespace game