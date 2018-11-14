#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "random.h"

namespace game
{
// Constants -------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------

// Buffers ---------------------------------------------------------------------------------
extern sf::Texture tPlayer;
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

enum class direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

}  // namespace game