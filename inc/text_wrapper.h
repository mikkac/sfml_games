#pragma once
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <sstream>
namespace game
{
using namespace sf;

class TextWrapper
{
  public:
    TextWrapper(const std::string& text, Font& font, int char_size, Color color,
                const Vector2f& pos);
    void set_position(const Vector2f& position);
    void set_string(const std::string& text);
    void center();
    sf::Text get_text() const { return text_; }

  private:
    sf::Text text_;
};

} // namespace game