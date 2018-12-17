#include "texture_holder.h"
#include <cassert>

namespace game
{
TextureHolder& TextureHolder::get_instance() {
    static TextureHolder instance{};
    return instance;
}

Texture& TextureHolder::get_texture(const std::string& filename) {
    // auto textures = get_instance().textures_;
    if (auto iterator{textures_.find(filename)}; iterator == textures_.end())
        textures_[filename].loadFromFile(filename);

    return textures_[filename];
}
} // namespace game
