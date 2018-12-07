#include "zombie.h"
#include "utils.h"
#include <cmath>
namespace game
{
Zombie::Zombie(const std::string& path, const Vector2f& pos, int speed, int health)
    : sprite_{Sprite(TextureHolder::get_texture(path))}, position_{pos},
      speed_{speed * (rand_num(kMaxVarriance) + kOffset) / 100.f}, health_{health} {
    sprite_.setOrigin(25.f, 25.f);
    sprite_.setPosition(position_);
}

bool Zombie::hit() {
    if (--health_ <= 0) {
        alive_ = false;
        sprite_.setTexture(TextureHolder::get_texture("res/graphics/blood.png"));
        return true;
    }
    return false;
}

void Zombie::update(float elapsed_time, Vector2f player_location) {
    float player_x = player_location.x;
    float player_y = player_location.y;

    if (player_x > position_.x) position_.x += speed_ * elapsed_time;
    if (player_x < position_.x) position_.x -= speed_ * elapsed_time;
    if (player_y > position_.y) position_.y += speed_ * elapsed_time;
    if (player_y < position_.y) position_.y -= speed_ * elapsed_time;

    sprite_.setPosition(position_);

    float angle = atan2(player_y - position_.y, player_x - position_.x) * 180 / 3.14;
    sprite_.setRotation(angle);
}

Bloater::Bloater(const Vector2f& pos)
    : Zombie("res/graphics/bloater.png", pos, kBloaterSpeed, kBloaterHealth) {}

Chaser::Chaser(const Vector2f& pos)
    : Zombie("res/graphics/chaser.png", pos, kChaserSpeed, kChaserHealth) {}

Crawler::Crawler(const Vector2f& pos)
    : Zombie("res/graphics/crawler.png", pos, kCrawlerSpeed, kCrawlerHealth) {}

void Horde::create_horde(unsigned num_of_zombies, const IntRect& arena) {
    for (auto& zombie : zombies)
        if (zombie) delete zombie;

    num_zombies = num_of_zombies;
    num_zombies_alive = num_of_zombies;

    int min_y = arena.top + 50;
    int max_y = arena.height - 50;
    int min_x = arena.left + 50;
    int max_x = arena.width - 50;

    for (unsigned idx = 0; idx < num_zombies; ++idx) {
        float x, y;
        int side{rand_num(3)};
        switch (side) {
            case 0: // left
                x = min_x;
                y = rand_num(max_y) + min_y;
                break;
            case 1: // right
                x = max_x;
                y = rand_num(max_y) + min_y;
                break;
            case 2: // top
                x = rand_num(max_x) + min_x;
                y = min_y;
                break;
            case 3: // bottom
                x = rand_num(max_x) + min_x;
                y = max_y;
                break;
        }

        // randomized type of zombie
        int type{rand_num(2)};
        switch (type) {
            case 0: zombies.push_back(new Bloater(Vector2f(x, y))); break;
            case 1: zombies.push_back(new Chaser(Vector2f(x, y))); break;
            case 2: zombies.push_back(new Crawler(Vector2f(x, y))); break;
        }
    }
}

Horde::~Horde() {
    for (auto& zombie : zombies)
        if (zombie) delete zombie;
}
} // namespace game