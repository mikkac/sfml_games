#pragma once
#include <SFML/Graphics.hpp>

namespace game
{
using namespace sf;
class Zombie
{
  public:
  private:
    const int kBloaterSpeed{40};
    const int kChaserSpeed{80};
    const int kCrawlerSpeed{20};

    const int kBloaterHealht{5};
    const int kChaserHealth{1};
    const int kCrawlerHealth{3};

    const int kMaxVarriance{20};

    Vector2f position_;
    Sprite sprite_;
    int speed_;
    int health_;
    bool alive_;
};

} // namespace game