#include "hud.h"

namespace game
{
Hud::Hud() {
    Vector2u resolution{VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height};
    font_.loadFromFile("res/fonts/Roboto-Light.ttf");

    start_ = TextWrapper("Press Enter when ready", font_, 100, Color::White, Vector2f{resolution.x/2.f, resolution.y/2.f});
    start_.center();

    time_ = TextWrapper("------", font_, 75, Color::White, Vector2f{resolution.x - 150.f, 0.f});

    level_ = TextWrapper("1", font_, 75, Color::White, Vector2f{25.f, 0.f});
    
}
} // namespace game
