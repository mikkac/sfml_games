#pragma once
#include "text_wrapper.h"
#include <SFML/Graphics.hpp>

namespace game
{
using namespace sf;
class Hud
{
  public:
    Hud();

    void update(float time_remaining, int current_level);

    Text get_message() const { return start_.get_text(); }
    Text get_time() const { return time_.get_text(); }
    Text get_level() const { return level_.get_text(); }

  private:
    Font font_;
    TextWrapper start_;
    TextWrapper time_;
    TextWrapper level_;

    static constexpr int frames_per_update{500};
    int frames_since_last_update{};
};

} // namespace game
