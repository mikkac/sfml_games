#pragma once
#include <SFML/Graphics.hpp>
#include <map>

namespace game
{
using namespace sf;

class TextureHolder
{
  public:
    TextureHolder() = default;
    TextureHolder(const TextureHolder& other) = delete;
    TextureHolder& operator=(const TextureHolder& other) = delete;

    static TextureHolder& get_instance();
    Texture& get_texture(const std::string& filename);

  private:
    std::map<std::string, Texture> textures_;
};
} // namespace game
