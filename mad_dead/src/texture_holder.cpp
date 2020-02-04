#include "texture_holder.h"
#include <cassert>

namespace game
{
TextureHolder* TextureHolder::instance_ = nullptr;

TextureHolder::TextureHolder() {
    assert(not instance_);
    instance_ = this;
}

Texture& TextureHolder::get_texture(const std::string& filename) {
    auto& textures = instance_->textures_;

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