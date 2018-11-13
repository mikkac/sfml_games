#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "random.h"

namespace game
{
// Constants -------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------

// Buffers ---------------------------------------------------------------------------------

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

struct vec2
{
    float x, y;
};

}  // namespace game