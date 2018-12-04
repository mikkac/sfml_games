#pragma once
#include "texture_holder.h"
#include <SFML/Graphics.hpp>
#include <vector>
namespace game
{
using namespace sf;

enum class ZombieType { BLOATER, CHASER, CRAWLER };
const int kBloaterSpeed{40};
const int kChaserSpeed{80};
const int kCrawlerSpeed{20};

const int kBloaterHealth{5};
const int kChaserHealth{1};
const int kCrawlerHealth{3};

const int kMaxVarriance{30};
const int kOffset{101 - kMaxVarriance};

class Zombie
{
  public:
    Zombie(const std::string& path, const Vector2f& pos, int speed, int health);
    bool hit();
    void update(float elapsed_time, Vector2f player_location);
    bool is_alive() const { return alive_; }
    FloatRect get_position() const { return sprite_.getGlobalBounds(); }
    Sprite get_sprite() const { return sprite_; }

  private:
    Sprite sprite_;
    Vector2f position_;
    int speed_;
    int health_;
    bool alive_{true};
};

class Bloater : public Zombie
{
  public:
    Bloater(const Vector2f& pos);
};

class Chaser : public Zombie
{
  public:
    Chaser(const Vector2f& pos);
};

class Crawler : public Zombie
{
  public:
    Crawler(const Vector2f& pos);
};

std::vector<Zombie*> create_horde(unsigned num_of_zombies, IntRect arena);

} // namespace game