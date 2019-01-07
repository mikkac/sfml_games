#pragma once
#include <SFML/Graphics.hpp>
#include "text_wrapper.h"

namespace game
{
using namespace sf;
class Hud
{
  public:
    Hud();

    void set_time(const std::string& text) { time_.set_string(text); }
    void set_level(const std::string& text) { level_.set_string(text); }

    Text get_message() const { return start_.get_text(); }
    Text get_time() const { return time_.get_text(); }
    Text get_level() const { return level_.get_text(); }

  private:
    Font font_;
    TextWrapper start_;
    TextWrapper time_;
    TextWrapper level_;
};

} // namespace game
