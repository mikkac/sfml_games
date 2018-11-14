#pragma once
#include "utils.h"
namespace game
{
class Player
{
public:
    Player();
    void spawn(const sf::Vector2f& resolution, const sf::IntRect& arena, int tileSize);
    void reset();
    bool hit(sf::Time timeHit);
    void update(float elapsedTime, sf::Vector2i mousePosition);

    // Boosts
    void upgradeHealt();
    void upgradeSpeed();
    void increaseHealth(int amount);

    // Move in a given direction
    void moveUp(bool isMoving);
    void moveDown(bool isMoving);
    void moveLeft(bool isMoving);
    void moveRight(bool isMoving);

    // Getters
    sf::FloatRect getPosition() const;
    sf::Vector2f getCenter() const;
    float getRotation() const;
    sf::Sprite getSprite() const;
    int getHealth() const;
    sf::Time getLastHitTime() const;

private:
    const float START_HEALTH{100.f};
    const float START_SPEED{200.f};
    sf::Vector2f mPosition;
    sf::Sprite mSprite;
    // sf::Texture mTexture;
    struct
    {
        bool up, down, left, right;
    } mKeyPressed;

    int mHealth{static_cast<int>(START_HEALTH)};
    int mMaxHealth{static_cast<int>(START_HEALTH)};
    float mSpeed{START_SPEED};  // speed in pixels per second
    sf::Time mLastHitTime;

    // Arena data
    struct
    {
        sf::Vector2f resolution;
        sf::IntRect arena;
        int tileSize;
    } mScreenSpace;
};

}  // namespace game