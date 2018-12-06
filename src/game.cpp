#include "game.h"

namespace game
{
void Game::update(Clock& clock, Screen& screen, Player& player, std::vector<Zombie*>& zombies,
                  Bullet* bullets, std::vector<Pickup*>& pickups) {
    Time dt = clock.restart();
    game_time_total_ += dt;
    mouse_screen_pos_ = Mouse::getPosition();

    // Convert mouse postition to world coords
    mouse_world_pos_ = screen.window.mapPixelToCoords(mouse_screen_pos_, screen.main_view);

    screen.crosshair.setPosition(mouse_world_pos_);
    float dt_as_sec{dt.asSeconds()};

    player.update(dt_as_sec, mouse_screen_pos_);
    screen.main_view.setCenter(player.get_center());

    for (auto& zombie : zombies)
        if (zombie->is_alive()) zombie->update(dt_as_sec, player.get_center());

    for (unsigned idx = 0; idx < 5; ++idx)
        if (bullets[idx].is_flying()) bullets[idx].update(dt_as_sec);

    for (auto& pickup : pickups) pickup->update(dt_as_sec);
}
} // namespace game