#include "texture_holder.h"
#include <cassert>

namespace game
{
TextureHolder& TextureHolder::get_instance() {
    static TextureHolder instance{};
    return instance;
}

Texture& TextureHolder::get_texture(const std::string& filename) {
    auto& textures = get_instance().textures_;

    auto iterator = textures.find(filename);
    if (iterator != textures.end()) {
        return iterator->second; // return existing texture
    } else {
        auto& new_texture = textures[filename];
        new_texture.loadFromFile(filename);
        return new_texture; // return new-created texture
    }
}
} // namespace game
