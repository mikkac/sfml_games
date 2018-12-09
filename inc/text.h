#pragma once
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <sstream>
namespace game
{
using namespace sf;

class Text
{
  public:
    Text(const std::string& text, Font& font, int char_size, Color color);
    void set_position(const Vector2f& position);
    void set_string(const std::string& text);
    void center();

  private:
    sf::Text text_;
};

} // namespace game