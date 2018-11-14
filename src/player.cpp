#include "player.h"
#include <cmath>
namespace game
{
Player::Player()
{
    mSprite.setTexture(tPlayer);
    mSprite.setOrigin(25, 25);
}

void Player::spawn(const sf::Vector2f& resolution, const sf::IntRect& arena, int tileSize)
{
    mPosition.x = arena.width / 2.f;
    mPosition.y = arena.height / 2.f;

    mScreenSpace.resolution = resolution;
    mScreenSpace.arena = arena;
    mScreenSpace.tileSize = tileSize;
}

void Player::reset()
{
    mHealth = static_cast<int>(START_HEALTH);
    mMaxHealth = static_cast<int>(START_HEALTH);
    mSpeed = START_SPEED;
}

bool Player::hit(sf::Time timeHit)
{
    if (timeHit.asMilliseconds() - mLastHitTime.asMilliseconds() > 200)
    {
        mLastHitTime = timeHit;
        mHealth -= 10;
        return true;
    }
    else
        return false;
}

void Player::update(float elapsedTime, sf::Vector2i mousePosition)
{
    float shift = elapsedTime * mSpeed;
    if (mKeyPressed.up) mPosition.y -= shift;
    if (mKeyPressed.down) mPosition.y += shift;
    if (mKeyPressed.left) mPosition.x -= shift;
    if (mKeyPressed.right) mPosition.x += shift;

    mSprite.setPosition(mPosition);

    // Keep the player in the area
    if (auto bound = mScreenSpace.arena.width - mScreenSpace.tileSize; mPosition.x > bound)
        mPosition.x = bound;

    if (auto bound = mScreenSpace.arena.left + mScreenSpace.tileSize; mPosition.x < bound)
        mPosition.x = bound;

    if (auto bound = mScreenSpace.arena.height - mScreenSpace.tileSize; mPosition.y > bound)
        mPosition.x = bound;

    if (auto bound = mScreenSpace.arena.top + mScreenSpace.tileSize; mPosition.x < bound)
        mPosition.x = bound;

    // Calculate the angle the player is facing
    float angle = (atan2(mousePosition.y - mScreenSpace.resolution.y / 2.f,
                         mousePosition.x - mScreenSpace.resolution.x / 2.f) *
                   180.0) /
                  3.1415;

    mSprite.setRotation(angle);
}

// Boosts -------------------------------------------------
void Player::upgradeHealth()
{
    mHealth += static_cast<int>(START_HEALTH * 0.2f);
}

void Player::upgradeSpeed()
{
    mSpeed += static_cast<int>(START_SPEED * 0.2f);
}

void Player::increaseHealth(int amount)
{
    mHealth += amount;
    if (mHealth > mMaxHealth) mHealth = mMaxHealth;
}

// Move ---------------------------------------------------
void Player::moveUp(bool isMoving)
{
    mKeyPressed.up = isMoving;
}

void Player::moveDown(bool isMoving)
{
    mKeyPressed.down = isMoving;
}

void Player::moveLeft(bool isMoving)
{
    mKeyPressed.left = isMoving;
}

void Player::moveRight(bool isMoving)
{
    mKeyPressed.right = isMoving;
}

// Getters ------------------------------------------------
sf::FloatRect Player::getPosition() const
{
    return mSprite.getGlobalBounds();
}

sf::Vector2f Player::getCenter() const
{
    return mPosition;
}

float Player::getRotation() const
{
    return mSprite.getRotation();
}

sf::Sprite Player::getSprite() const
{
    return mSprite;
}

int Player::getHealth() const
{
    return mHealth;
}

sf::Time Player::getLastHitTime() const
{
    return mLastHitTime;
}

}  // namespace game