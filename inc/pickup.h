#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace game
{
using namespace sf;

enum class PickupType { HEALTH, AMMO };

const int kHealthStartValue{50};
const int kAmmoStartValue{12};

class Pickup
{
  public:
    Pickup(const std::string& path, int value, const IntRect& arena);
    void update(float elapsed_time);
    void upgrade(PickupType type);
    int got_it();
    bool is_spawned() const { return spawned_; }
    FloatRect get_position() const { return sprite_.getGlobalBounds(); }
    Sprite get_sprite() const { return sprite_; }

  private:
    void set_arena(IntRect arena);
    void randomise_location();

  private:
    const float kStartWaitTime{10.f};
    const float kStartSecondsToLive{5.f};

    Sprite sprite_;
    IntRect arena_;
    int value_{};
    bool spawned_{false};
    float sec_since_spawn{};
    float sec_since_despawn{};
    float sec_to_live{kStartSecondsToLive};
    float sec_to_wait{kStartWaitTime};
};

class HealthPickup : public Pickup
{
  public:
    HealthPickup(const IntRect& arena)
        : Pickup("res/graphics/health_pickup.png", kHealthStartValue, arena) {}
    void upgrade() { Pickup::upgrade(PickupType::HEALTH); }

  private:
};

class AmmoPickup : public Pickup
{
  public:
    AmmoPickup(const IntRect& arena)
        : Pickup("res/graphics/ammo_pickup.png", kAmmoStartValue, arena) {}
    void upgrade() { Pickup::upgrade(PickupType::AMMO); }

  private:
};

} // namespace game