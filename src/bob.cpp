#include "bob.h"
#include "texture_holder.h"

namespace game
{
Bob::Bob() {
    sprite_ = Sprite(TextureHolder::get_instance().get_texture("res/graphics/bob.png"));
    motion_.jump_duration = 0.25f;
}
bool Bob::handle_input() {
    motion_.just_jumped = false;

    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        if (not motion_.is_jumping && not motion_.is_falling) {
            motion_.is_jumping = true;
            motion_.time_of_jump = 0;
            motion_.just_jumped = true;
        }
    } else {
        stop_jump();
    }

    if (Keyboard::isKeyPressed(Keyboard::Left))
        motion_.left = true;
    else
        motion_.left = false;

    if(Keyboard::isKeyPressed(Keyboard::Right))
        motion_.right = true;
    else
        motion_.right = false;

    return motion_.just_jumped;
}
} // namespace game
