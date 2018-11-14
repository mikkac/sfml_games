#pragma once
#include "utils.h"
namespace game
{
class Player
{
    void reset();
    bool hit(sf::Time timeHit);
    void update(float elapsedTime, sf::Vector2i mousePosition);

    // Boosts
    void upgradeSpeed();
    void upgradeHealt();
    void increaseHealth(int amount);

    // Move in a given direction
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    // Stop moving in a given direction
    void stopUp();
    void stopDown();
    void stopLeft();
    void stopRight();

    // Getters
    sf::FloatRect getPosition() const;
    sf::Vector2f getCenter() const;
    float getRotation() const;
    sf::Sprite getSprite() const;
    int getHealth() const;
    sf::Time getLastHitTime() const;

private:
    const float START_SPEED{200.f};
    const float START_HEALTH{100.f};
    sf::Vector2f mPosition;
    sf::Sprite mSprite;
    // sf::Texture mTexture;
    struct
    {
        bool up, down, left, right;
    } mKeyPressed;

    int mHealth;
    int mMaxHealth;
    sf::Time mLastHitTime;
    float mSpeed;  // speed in pixels per second
};

}  // namespace game