#include "drawing.h"

namespace timber
{

//Buffers -----------------------------------------------------------------------------------
sf::Texture textureBackground = createBuffer<sf::Texture>("res/graphics/background.png");
sf::Texture textureBee = createBuffer<sf::Texture>("res/graphics/bee.png");
sf::Texture textureCloud = createBuffer<sf::Texture>("res/graphics/cloud.png");
sf::Texture textureTree = createBuffer<sf::Texture>("res/graphics/tree.png");
sf::Texture textureBranch = createBuffer<sf::Texture>("res/graphics/branch.png");
sf::Texture textureLog = createBuffer<sf::Texture>("res/graphics/log.png");
sf::Texture textureAxe = createBuffer<sf::Texture>("res/graphics/axe.png");
sf::Texture texturePlayer = createBuffer<sf::Texture>("res/graphics/player.png");
sf::Texture textureGravestone = createBuffer<sf::Texture>("res/graphics/rip.png");

sf::SoundBuffer soundChop = createBuffer<sf::SoundBuffer>("res/sound/chop.wav");
sf::SoundBuffer soundDeath = createBuffer<sf::SoundBuffer>("res/sound/death.wav");
sf::SoundBuffer soundOutOfTime = createBuffer<sf::SoundBuffer>("res/sound/out_of_time.wav");
//-------------------------------------------------------------------------------------------

//Constants --------------------------------------------------------------------------------
constexpr int WIDTH{ 1920 };
constexpr int HEIGHT{ 1080 };
constexpr int HIDDEN_X { WIDTH + 300 };
constexpr int HIDDEN_Y { HEIGHT + 300 };
constexpr int NUM_BRANCHES{ 6 };
constexpr int NUM_CLOUDS{ 5 };
constexpr float AXE_POSITION_LEFT{ 700 };
constexpr float AXE_POSITION_RIGHT{ 1075 };
//------------------------------------------------------------------------------------------

Drawing::Drawing(sf::Texture texture, bool is_active, vec2 position, vec2 speed) 
    : m_is_active{ is_active }, m_speed{ speed }
{
    m_sprite.setTexture(texture);
    setPosition(position);
}

void  Drawing::setPosition(vec2 position)
{
    m_sprite.setPosition(position.x, position.y);
}

vec2 Drawing::getPosition() const
{
    return vec2{ m_sprite.getPosition().x, m_sprite.getPosition().y };
}

void  Drawing::setSpeed(vec2 speed)
{
    m_speed = speed;
}

vec2 Drawing::getSpeed() const
{
    return m_speed;
}

bool Drawing::isActive() const
{
    return m_is_active;
}

void Drawing::setActiveness(bool is_active)
{
    m_is_active = is_active;
}

} //namespace timber
