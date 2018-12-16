#include "thomas.h"
#include "texture_holder.h"

namespace game
{
Thomas::Thomas() {
    sprite_ = Sprite(TextureHolder::get_texture("res/graphics/thomas.png"));
    motion_.jump_duration = 0.45f;
}
bool Thomas::handle_input() {
    motion_.just_jumped = false;

    if (Keyboard::isKeyPressed(Keyboard::W)) {
        if (not motion_.is_jumping && not motion_.is_falling) {
            motion_.is_jumping = true;
            motion_.time_of_jump = 0;
            motion_.just_jumped = true;
        }
    } else {
        stop_jump();
    }

    if (Keyboard::isKeyPressed(Keyboard::A))
        motion_.left = true;
    else
        motion_.left = false;

    if(Keyboard::isKeyPressed(Keyboard::D))
        motion_.right = true;
    else
        motion_.right = false;

    return motion_.just_jumped;
}
} // namespace game
