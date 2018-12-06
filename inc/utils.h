#pragma once
#include "random.h"
#include "texture_holder.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace game
{
// Buffers ---------------------------------------------------------------------------------
extern TextureHolder holder;
//------------------------------------------------------------------------------------------

// Rest of global variables ----------------------------------------------------------------
extern Random rand_num;
//------------------------------------------------------------------------------------------

} // namespace game