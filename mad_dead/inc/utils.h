#pragma once
#include "random.h"
#include "texture_holder.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace game
{
// Consts ----------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------

// Buffers ---------------------------------------------------------------------------------
extern TextureHolder holder;
extern Texture texture_background;
//------------------------------------------------------------------------------------------

// Rest of global variables ----------------------------------------------------------------
extern Random rand_num;
//------------------------------------------------------------------------------------------

} // namespace game