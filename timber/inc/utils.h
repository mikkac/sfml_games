#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "random.h"

namespace timber
{
// Constants -------------------------------------------------------------------------------
constexpr int WIDTH{1920};
constexpr int HEIGHT{1080};
constexpr int HIDDEN_X{WIDTH + 300};
constexpr int HIDDEN_Y{HEIGHT + 300};
constexpr int NUM_BRANCHES{6};
constexpr int NUM_CLOUDS{3};
constexpr float AXE_POSITION_LEFT{700.f};
constexpr float AXE_POSITION_RIGHT{1075.f};
constexpr float TIME_BAR_WIDTH{400.f};
constexpr float TIME_BAR_HEIGHT{80.f};
//------------------------------------------------------------------------------------------

// Buffers ---------------------------------------------------------------------------------
extern sf::Texture textureBackground;
extern sf::Texture textureBee;
extern sf::Texture textureCloud;
extern sf::Texture textureTree;
extern sf::Texture textureBackgroundTree;
extern sf::Texture textureBranch;
extern sf::Texture textureLog;
extern sf::Texture textureAxe;
extern sf::Texture texturePlayer;
extern sf::Texture textureGravestone;

extern sf::SoundBuffer soundBufferChop;
extern sf::SoundBuffer soundBufferDeath;
extern sf::SoundBuffer soundBufferOutOfTime;

extern sf::Font font;
//------------------------------------------------------------------------------------------

// Rest of global variables ----------------------------------------------------------------
extern Random rand_num;
//------------------------------------------------------------------------------------------

template <typename T>
T createBuffer(const char* pathToFile)
{
    T buffer;
    buffer.loadFromFile(pathToFile);
    return buffer;
}

enum class Side
{
    NONE,
    LEFT,
    RIGHT
};

struct vec2
{
    float x, y;
};

}  // namespace timber