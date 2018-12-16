#include "engine.h"
namespace game
{
Engine::Engine() {
    // Get the screen resolution
    Vector2f resolution{static_cast<float>(VideoMode::getDesktopMode().width),
                        static_cast<float>(VideoMode::getDesktopMode().height)};

    // Initialize window
    window_.create(VideoMode(resolution.x, resolution.y), "Bob was alone", Style::Fullscreen);

    views_.main.setSize(resolution);
    views_.hud.reset(FloatRect(0, 0, resolution.x, resolution.y));

    views_.left.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
    views_.right.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
    views_.bg_left.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
    views_.bg_right.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

    background_texture_ = TextureHolder::get_texture("res/graphics/background.png");
    background_sprite_.setTexture(background_texture_);
}

void Engine::run() {
    while (window_.isOpen()) {
        Time dt = time_.clock.restart();
        time_.game_total_time += dt;

        input();
        update(dt.asSeconds());
        draw();
    }
}
} // namespace game

