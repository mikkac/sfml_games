#include "hud.h"
#include <sstream>

namespace game
{
Hud::Hud() {
    Vector2u resolution{VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height};
    font_.loadFromFile("res/fonts/Roboto-Light.ttf");

    start_ = TextWrapper("Press Enter when ready", font_, 100, Color::White, Vector2f{resolution.x / 2.f, resolution.y / 2.f});
    start_.center();

    time_ = TextWrapper("------", font_, 75, Color::White, Vector2f{resolution.x - 150.f, 0.f});

    level_ = TextWrapper("1", font_, 75, Color::White, Vector2f{25.f, 0.f});
}

void Hud::update(float time_remaining, int current_level) {
    if (++frames_since_last_update > frames_per_update) {
        std::stringstream ss_time, ss_level;

        ss_time << static_cast<int>(time_remaining);
        time_.set_string(ss_time.str());

        ss_level << "Level: " << current_level;
        level_.set_string(ss_level.str());

        frames_since_last_update = 0;
    }
}
} // namespace game
