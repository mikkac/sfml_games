#include "sounds.h"

namespace game
{
Sound Sounds::create_sound(const std::string& path, AudioType type) {
    buffers_[static_cast<int>(type)].loadFromFile(path);
    return Sound{buffers_[static_cast<int>(type)]};
}

Sounds& Sounds::get_instance() {
    static Sounds instance{};
    return instance;
}

} // namespace game
