#include "utils.h"
namespace game
{
// Buffers -----------------------------------------------------------------------------------
Texture texture_player = create_buffer<Texture>("res/graphics/characters/manBlue_machine.png");
Texture texture_background = create_buffer<Texture>("res/graphics/background_64x64.png");
//-------------------------------------------------------------------------------------------

// Rest of global variables ----------------------------------------------------------------
Random rand_num;
//------------------------------------------------------------------------------------------

} // namespace game