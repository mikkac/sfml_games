#include "game.h"

namespace game
{
void Game::update(Clock& clock, Screen& screen, Player& player) {
    Time dt = clock.restart();
    game_time_total_ += dt;
    mouse_screen_pos_ = Mouse::getPosition();

    // Convert mouse postition to world coords
    mouse_world_pos_ = screen.window.mapPixelToCoords(mouse_screen_pos_, screen.main_view);

    player.update(dt.asSeconds(), mouse_screen_pos_);
    screen.main_view.setCenter(player.get_center());
}
} // namespace game