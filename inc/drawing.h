#pragma once
#include "utils.h"
namespace timber 
{

class Drawing
{
public:
    Drawing(
        sf::RenderWindow& window,
        sf::Texture& texture, 
        vec2 position = { 0,0 }
    );

    virtual ~Drawing() = default;

    virtual void draw();
    void setOrigin(int x, int y);

    vec2 getPosition() const;
    void setPosition(vec2 position);

protected:
    sf::RenderWindow& mWindow;
    sf::Sprite mSprite;
};

class Movable // movable means that object has some speed 
{
public:
    Movable(vec2 speed = {0, 0});

    virtual ~Movable() = default;

    vec2 getSpeed() const;
    void setSpeed(vec2 speed);
    
    vec2 mSpeed{};
    bool mIsActive{ false };
};

class Bee: public Drawing, public Movable
{
public:
    Bee(
        sf::RenderWindow& window,
        sf::Texture& texture, 
        vec2 position = { 0,0 },
        vec2 speed = { 0,0 }
    );

    void fly(float timeAsSeconds);
};

class Cloud: public Drawing, public Movable
{
public:
    Cloud(
        sf::RenderWindow& window,
        sf::Texture& texture,
        vec2 position = { 0,0 },
        vec2 speed = { 0,0 }
    );

    void fly(float timeAsSeconds);
};

class Log: public Drawing, public Movable
{
public:
    Log(
        sf::RenderWindow& window,
        sf::Texture& texture, 
        vec2 position = { 0,0 },
        vec2 speed = { 0,0 }
    );

    void fly(float timeAsSeconds);
    bool isActive() const;
    void setActive(bool isActive);
};

class Player: public Drawing
{
public:
    Player(
        sf::RenderWindow& window,
        sf::Texture& texturePlayerAlive,
        sf::Texture& texturePlayerDead,
        vec2 position = {0, 0}
    );

    Side getSide() const;
    void setSide(Side side);

    bool isAlive() const;
    void die();
    void reset();

private:
    sf::Texture& mTextureDead;
    sf::Texture& mTextureAlive;
    Side mSide;
    bool mIsAlive;
};

class Axe: public Drawing
{
public:
    Axe(
        sf::RenderWindow& window,
        sf::Texture& texture,
        vec2 position = {0, 0}
    );

    Side getSide() const;
    void setSide(Side side);
    
private:
    Side mSide;
};

class Branch: public Drawing
{
public:
    Branch(
        sf::RenderWindow& window,
        sf::Texture& texture,
        vec2 position = {0, 0}
    );

    Side getSide() const;
    void setSideAndHeight(Side side, float height);
    
private:
    Side mSide;
};



} //namespace timber
