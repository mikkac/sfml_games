#include "pickup.h"
#include "utils.h"
namespace game
{
Pickup::Pickup(const std::string& path, int value, const IntRect& arena)
    : sprite_{Sprite(holder.get_texture(path))}, value_{value} {
    sprite_.setOrigin(25.f, 25.f);
    set_arena(arena);
    randomise_location();
}

void Pickup::update(float elapsed_time) {
    if (spawned_)
        sec_since_spawn += elapsed_time;
    else
        sec_since_despawn += elapsed_time;

    if (spawned_ && sec_since_spawn > sec_to_live) {
        spawned_ = false;
        sec_since_despawn = 0.f;
    }

    if (not spawned_ && sec_since_despawn > sec_to_wait) randomise_location();
}

void Pickup::upgrade(PickupType type) {
    switch (type) {
        case PickupType::HEALTH: value_ += kHealthStartValue / 2.f; break;
        case PickupType::AMMO: value_ += kAmmoStartValue / 2.f; break;
    }
    sec_to_live += kStartSecondsToLive / 10.f;
    sec_to_wait -= kStartWaitTime / 10.f;
}

int Pickup::got_it() {
    spawned_ = false;
    sec_since_despawn = 0.f;
    return value_;
}

void Pickup::set_arena(IntRect arena) {
    arena_ = IntRect{arena.left + 50, arena.top + 50, arena.width - 50, arena.height - 50};
}

void Pickup::randomise_location() {
    int x{rand_num(arena_.width)};
    int y{rand_num(arena_.height)};
    sprite_.setPosition(x, y);
    sec_since_spawn = 0.f;
    spawned_ = true;
}
} // namespace game