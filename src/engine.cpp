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
        time_.game_total += dt;

        input();
        update(dt.asSeconds());
        draw();
    }
}

void Engine::input() {
    Event event;
    while (window_.pollEvent(event)) {
        if (event.type == Event::KeyPressed) {
            // Quit the game
            if (Keyboard::isKeyPressed(Keyboard::Escape)) window_.close();

            // Start the game
            if (Keyboard::isKeyPressed(Keyboard::Return)) playing_ = true;

            // Switch between Thomas & Bob
            if (Keyboard::isKeyPressed(Keyboard::Q)) character_one_ = !character_one_;
            ;

            // Switch between full and split screen
            if (Keyboard::isKeyPressed(Keyboard::E)) split_screen_ = !split_screen_;
        }
    }
}

void Engine::update(float dt_as_seconds) {
    if (playing_) {
        time_.remaining -= dt_as_seconds;
        if (time_.remaining <= 0) new_level_required_ = true;
    }
}

void Engine::draw() {
    window_.clear(Color::White);

    if (not split_screen_) {
        window_.setView(views_.bg_main);
        window_.draw(background_sprite_);
        window_.setView(views_.main);
    } else {
        // First draw Thomas
        window_.setView(views_.bg_left);
        window_.draw(background_sprite_);
        window_.setView(views_.left);

        // Now draw Bob
        window_.setView(views_.bg_right);
        window_.draw(background_sprite_);
        window_.setView(views_.right);
    }

    // Draw hud
    window_.setView(views_.hud);

    window_.display();
}

} // namespace game

