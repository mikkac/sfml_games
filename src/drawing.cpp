#include "drawing.h"
namespace timber
{
Drawing::Drawing(sf::RenderWindow &window, sf::Texture &texture, vec2 position) : mWindow{window}
{
    mSprite.setTexture(texture);
    setPosition(position);
}

void Drawing::draw()
{
    mWindow.draw(mSprite);
}

void Drawing::setOrigin(int x, int y)
{
    mSprite.setOrigin(x, y);
}

vec2 Drawing::getPosition() const
{
    return vec2{mSprite.getPosition().x, mSprite.getPosition().y};
}

void Drawing::setPosition(vec2 position)
{
    mSprite.setPosition(position.x, position.y);
}

Movable::Movable(vec2 speed) : mSpeed{speed}
{
}

vec2 Movable::getSpeed() const
{
    return mSpeed;
}

void Movable::setSpeed(vec2 speed)
{
    mSpeed = speed;
}

Bee::Bee(sf::RenderWindow &window, sf::Texture &texture, vec2 position, vec2 speed)
    : Drawing(window, texture, position), Movable(speed)
{
}

void Bee::fly(float timeAsSeconds)  // Move the bee
{
    if (!mIsActive)
    {
        setSpeed(vec2{rand_num(100) + 300, 0});  // how fast is the bee
        setPosition(vec2{2000, rand_num(700)});  // how high is the bee
        mIsActive = true;
    }
    else
    {
        setPosition(vec2{getPosition().x - (getSpeed().x * timeAsSeconds), getPosition().y});
        if (getPosition().x < 0) mIsActive = false;
    }
}

Cloud::Cloud(sf::RenderWindow &window, sf::Texture &texture, vec2 position, vec2 speed)
    : Drawing(window, texture, position), Movable(speed)
{
}

void Cloud::fly(float timeAsSeconds)  // Move the cloud
{
    if (!mIsActive)
    {
        setSpeed(vec2{rand_num(100), 0});                  // how fast is the cloud
        setPosition(vec2{rand_num(1000), rand_num(200)});  // how high is the cloud
        mIsActive = true;
    }
    else
    {
        setPosition(vec2{getPosition().x + (getSpeed().x * timeAsSeconds), getPosition().y});
        if (getPosition().x > WIDTH || getPosition().x < 0) mIsActive = false;
    }
}

Log::Log(sf::RenderWindow &window, sf::Texture &texture, vec2 position, vec2 speed)
    : Drawing(window, texture, position), Movable(speed)
{
}

void Log::fly(float timeAsSeconds)
{
    if (mIsActive)
    {
        setPosition(vec2{getPosition().x + (getSpeed().x * timeAsSeconds),
                         getPosition().y + (getSpeed().y * timeAsSeconds)});

        if (getPosition().x < -100 ||
            getPosition().x > WIDTH + 200)  // Has the log reached the edge of screen?
        {
            mIsActive = false;
            setPosition(vec2{810, 720});
        }
    }
}

bool Log::isActive() const
{
    return mIsActive;
}

void Log::setActive(bool isActive)
{
    mIsActive = isActive;
}

Player::Player(sf::RenderWindow &window, sf::Texture &texturePlayerAlive,
               sf::Texture &texturePlayerDead, vec2 position)
    : Drawing(window, texturePlayerAlive, position),
      mTextureDead{texturePlayerDead},
      mTextureAlive{texturePlayerAlive}
{
}

Side Player::getSide() const
{
    return mSide;
}

void Player::setSide(Side side)
{
    mSide = side;
    switch (mSide)
    {
        case Side::LEFT:
            setPosition(vec2{580, 720});
            break;
        case Side::RIGHT:
            setPosition(vec2{1200, 720});
            break;
        case Side::NONE:  // Hide the branch
            setPosition(vec2{HIDDEN_X, getPosition().y});
            break;
        default:
            break;
    }
}

bool Player::isAlive() const
{
    return mIsAlive;
}

void Player::die()
{
    mIsAlive = false;
    setPosition(vec2{getPosition().x, 800});
    mSprite.setTexture(mTextureDead);
}

void Player::reset()
{
    mIsAlive = true;
    setPosition(vec2{580, 720});
    mSprite.setTexture(mTextureAlive);
}

Axe::Axe(sf::RenderWindow &window, sf::Texture &texture, vec2 position)
    : Drawing(window, texture, position)
{
}

Side Axe::getSide() const
{
    return mSide;
}

void Axe::setSide(Side side)
{
    mSide = side;
    switch (mSide)
    {
        case Side::LEFT:
            setPosition(vec2{AXE_POSITION_LEFT, getPosition().y});
            break;
        case Side::RIGHT:
            setPosition(vec2{AXE_POSITION_RIGHT, getPosition().y});
            break;
        case Side::NONE:
            setPosition(vec2{HIDDEN_X, getPosition().y});
            break;
        default:
            break;
    }
}

Branch::Branch(sf::RenderWindow &window, sf::Texture &texture, vec2 position)
    : Drawing(window, texture, position)
{
}

Side Branch::getSide() const
{
    return mSide;
}

void Branch::setSideAndHeight(Side side, float height)
{
    mSide = side;
    switch (mSide)
    {
        case Side::LEFT:  // Move the branch to the left side and rotate
            setPosition(vec2{610, height});
            mSprite.setRotation(180);
            break;
        case Side::RIGHT:  // Move the branch to the right side and don't rotate
            setPosition(vec2{1330, height});
            mSprite.setRotation(0);
            break;
        case Side::NONE:  // Hide the branch
            setPosition(vec2{HIDDEN_X, height});
            break;
        default:
            break;
    }
}

}  // namespace timber
