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

Screen::Screen() {
    // Get the screen resolution
    Vector2f resolution{static_cast<float>(VideoMode::getDesktopMode().width),
                        static_cast<float>(VideoMode::getDesktopMode().height)};

    // Initialize window
    window.create(VideoMode(resolution.x, resolution.y), "Bob was alone", Style::Fullscreen);

    background_texture = TextureHolder::get_instance().get_texture("res/graphics/background.png");
    background_sprite.setTexture(background_texture);
    views = Views(resolution);
}

void Engine::run() {
    while (screen_.window.isOpen()) {
        Time dt = time_.clock.restart();
        time_.game_total += dt;

        input();
        update(dt.asSeconds());
        draw();
    }
}

void Engine::input() {
    Event event;
    while (screen_.window.pollEvent(event)) {
        if (event.type == Event::KeyPressed) {
            // Quit the game
            if (Keyboard::isKeyPressed(Keyboard::Escape)) screen_.window.close();

            // Start the game
            if (Keyboard::isKeyPressed(Keyboard::Return)) playing_ = true;

            // Switch between Thomas & Bob
            if (Keyboard::isKeyPressed(Keyboard::Q)) character_focus_ = !character_focus_;

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
    if (new_level_required_) { load_level(); }

    if (playing_) {
        thomas_.update(dt_as_seconds);
        bob_.update(dt_as_seconds);

        time_.remaining -= dt_as_seconds;
        if (time_.remaining <= 0) new_level_required_ = true;
    }

    if (split_screen_) {
        screen_.views.left.setCenter(thomas_.get_center());
        screen_.views.right.setCenter(bob_.get_center());
    } else {
        if (character_focus_)
            screen_.views.main.setCenter(thomas_.get_center());
        else
            screen_.views.main.setCenter(bob_.get_center());
    }
}

void Engine::draw() {
    screen_.window.clear(Color::White);

    if (not split_screen_) {
        draw_split_screen();
    } else {
        draw_main_scrren();
    }
    draw_hud();
    screen_.window.display();
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

void Engine::draw_split_screen() {
    screen_.window.setView(screen_.views.bg_main);
    screen_.window.draw(screen_.background_sprite);
    screen_.window.setView(screen_.views.main);
    screen_.window.draw(level_manager_.get_vertex_array(), &level_manager_.get_texture_tiles());
    screen_.window.draw(thomas_.get_sprite());
    screen_.window.draw(bob_.get_sprite());
}

void Engine::draw_main_scrren() {
    // First draw Thomas
    screen_.window.setView(screen_.views.bg_left);
    screen_.window.draw(screen_.background_sprite);
    screen_.window.setView(screen_.views.left);

    screen_.window.draw(level_manager_.get_vertex_array(), &level_manager_.get_texture_tiles());
    screen_.window.draw(bob_.get_sprite());
    screen_.window.draw(thomas_.get_sprite());

    // Now draw Bob
    screen_.window.setView(screen_.views.bg_right);
    screen_.window.draw(screen_.background_sprite);
    screen_.window.setView(screen_.views.right);

    screen_.window.draw(level_manager_.get_vertex_array(), &level_manager_.get_texture_tiles());
    screen_.window.draw(thomas_.get_sprite());
    screen_.window.draw(bob_.get_sprite());
}

void Engine::draw_hud() {
    screen_.window.setView(screen_.views.hud);
}
} // namespace game

