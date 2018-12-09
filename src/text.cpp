#include "text.h"
namespace timber
{
Text::Text(const std::string& text, Font& font, int char_size, Color color) {
    text_.setFont(font);
    text_.setString(text);
    text_.setCharacterSize(char_size);
    text_.setFillColor(color);
}

void Text::set_position(const Vector2f& position) {
    text_.setPosition(position.x, position.y);
}

void Text::set_string(const std::string& text) {
    text_.setString(text);
}

void Text::center() {
    FloatRect text_rect = text_.getLocalBounds();
    text_.setOrigin(text_rect.left + text_rect.width / 2.f, text_rect.top + text_rect.height / 2.f);
}

} // namespace timber