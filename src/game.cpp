#include "game.h"

namespace game
{
void Game::update(Clock& clock, Screen& screen, Player& player, std::vector<Zombie*>& zombies,
                  Weapon& weapon, std::vector<Pickup*>& pickups) {
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

    for (auto& bullet : weapon.bullets)
        if (bullet.is_flying()) bullet.update(dt_as_sec);

    for (auto& pickup : pickups) pickup->update(dt_as_sec);
}

void Game::detect_collision(Bullet* bullets, std::vector<Zombie*>& zombies) {
    if (not bullets) return;
    for (unsigned idx = 0; idx < kBulletsArraySize; ++idx) {
        for (auto& zombie : zombies) {
            if (bullets[idx].is_flying() && zombie->is_alive()) {
                if (bullets[idx].get_position().intersects(zombie->get_position())) {
                    bullets[idx].stop();
                    if (zombie->hit()) {
                        score_ += 10;
                        // NEED TO CREATE HORDE CLASS
                    }
                }
            }
        }
    }
}
} // namespace game