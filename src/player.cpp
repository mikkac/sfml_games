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

sf::Sprite Player::getSprite() const
{
    return mSprite;
}

}  // namespace game