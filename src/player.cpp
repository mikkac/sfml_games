#include "player.h"

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