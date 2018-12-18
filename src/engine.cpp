#include "engine.h"
namespace game
{
Views::Views(const Vector2f& resolution) {
    main.setSize(resolution);
    hud.reset(FloatRect(0, 0, resolution.x, resolution.y));

    left.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
    right.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
    bg_left.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
    bg_right.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));
}

Engine::Engine() {
    // Get the screen resolution
    Vector2f resolution{static_cast<float>(VideoMode::getDesktopMode().width),
                        static_cast<float>(VideoMode::getDesktopMode().height)};

    // Initialize window
    window_.create(VideoMode(resolution.x, resolution.y), "Bob was alone", Style::Fullscreen);

    views_ = Views(resolution);

    background_texture_ = TextureHolder::get_instance().get_texture("res/graphics/background.png");
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
        // TODO shouldn't next two if's be in if condition above?
        if (thomas_.handle_input()) { /* play a jump sound */
        }
        if (bob_.handle_input()) { /* play a jump sound */
        }
    }
}

void Engine::update(float dt_as_seconds) {
    if (new_level_required_) { // TODO create load_level() function
        thomas_.spawn(Vector2f(0.f, 0.f), kGravity);
        bob_.spawn(Vector2f(100.f, 0.f), kGravity);

        time_.remaining = 10.f;
        new_level_required_ = false;

        level_manager_.load_next_level();
    }

    if (playing_) {
        thomas_.update(dt_as_seconds);
        bob_.update(dt_as_seconds);

        time_.remaining -= dt_as_seconds;
        if (time_.remaining <= 0) new_level_required_ = true;
    }

    if (split_screen_) {
        views_.left.setCenter(thomas_.get_center());
        views_.right.setCenter(bob_.get_center());
    } else {
        if (character_one_)
            views_.main.setCenter(thomas_.get_center());
        else
            views_.main.setCenter(bob_.get_center());
    }
}

void Engine::draw() {
    window_.clear(Color::White);

    if (not split_screen_) {
        window_.setView(views_.bg_main);
        window_.draw(background_sprite_);
        window_.setView(views_.main);

        window_.draw(level_manager_.get_vertex_array(), &level_manager_.get_texture_tiles());
        window_.draw(thomas_.get_sprite());
        window_.draw(bob_.get_sprite());

    } else {
        // First draw Thomas
        window_.setView(views_.bg_left);
        window_.draw(background_sprite_);
        window_.setView(views_.left);

        window_.draw(level_manager_.get_vertex_array(), &level_manager_.get_texture_tiles());
        window_.draw(bob_.get_sprite());
        window_.draw(thomas_.get_sprite());

        // Now draw Bob
        window_.setView(views_.bg_right);
        window_.draw(background_sprite_);
        window_.setView(views_.right);

        window_.draw(level_manager_.get_vertex_array(), &level_manager_.get_texture_tiles());
        window_.draw(thomas_.get_sprite());
        window_.draw(bob_.get_sprite());
    }

    // Draw hud
    window_.setView(views_.hud);

    window_.display();
}

void Engine::load_level() {
    playing_ = false;
    level_manager_.delete_current_level();
    level_manager_.load_next_level();

    time_.remaining = level_manager_.get_time_limit();

    thomas_.spawn(level_manager_.get_start_pos(), kGravity);
    bob_.spawn(level_manager_.get_start_pos(), kGravity);

    new_level_required_ = false;
}
} // namespace game

