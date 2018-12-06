#include "game.h"

namespace game
{
void Game::update(Clock& clock, Screen& screen, Player& player, std::vector<Zombie*>& zombies,
                  Bullet* bullets) {
    Time dt = clock.restart();
    game_time_total_ += dt;
    mouse_screen_pos_ = Mouse::getPosition();

    // Convert mouse postition to world coords
    mouse_world_pos_ = screen.window.mapPixelToCoords(mouse_screen_pos_, screen.main_view);

    player.update(dt.asSeconds(), mouse_screen_pos_);
    screen.main_view.setCenter(player.get_center());

    for (auto& zombie : zombies)
        if (zombie->is_alive()) zombie->update(dt.asSeconds(), player.get_center());

    for (unsigned idx = 0; idx < 100; ++idx)
        if (bullets[idx].is_flying()) bullets[idx].update(dt.asSeconds());
}
} // namespace game