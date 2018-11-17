#pragma once
#include "random.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

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

template<typename T>
T createBuffer(const char* pathToFile) {
    T buffer;
    buffer.loadFromFile(pathToFile);
    return buffer;
}

enum class State { PAUSE, LEVEL_UP, GAME_OVER, PLAY };

} // namespace game