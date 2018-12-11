#include "utils.h"

namespace game
{
// Buffers -----------------------------------------------------------------------------------;
TextureHolder holder;
Texture texture_background{holder.get_texture("res/graphics/background_sheet.png")};

//-------------------------------------------------------------------------------------------

// Rest of global variables ----------------------------------------------------------------
Random rand_num;
//------------------------------------------------------------------------------------------

} // namespace game