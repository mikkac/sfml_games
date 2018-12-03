#pragma once
#include <SFML/Graphics.hpp>
#include <map>

namespace game
{
using namespace sf;

class TextureHolder
{
  public:
    TextureHolder();
    static Texture& get_texture(const std::string& filename);

  private:
    std::map<std::string, Texture> textures_;
    static TextureHolder* instance_;
};
} // namespace game