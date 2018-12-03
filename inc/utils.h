#pragma once
#include "random.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace game
{
// Constants -------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------

// Buffers ---------------------------------------------------------------------------------
extern Texture texture_player;
extern Texture texture_background;
//------------------------------------------------------------------------------------------

// Rest of global variables ----------------------------------------------------------------
extern Random rand_num;
//------------------------------------------------------------------------------------------

template<typename T>
T create_buffer(const char* pathToFile) {
    T buffer;
    buffer.loadFromFile(pathToFile);
    return buffer;
}

} // namespace game