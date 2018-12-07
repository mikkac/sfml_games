#include "game.h"

namespace game
{
void Game::update(Clock& clock, Screen& screen, Player& player, Horde& horde, Weapon& weapon,
                  std::array<Pickup*, 2>& pickups) {
    Time dt = clock.restart();
    game_time_total_ += dt;
    mouse_screen_pos_ = Mouse::getPosition();

    // Convert mouse postition to world coords
    mouse_world_pos_ = screen.window.mapPixelToCoords(mouse_screen_pos_, screen.main_view);

    screen.crosshair.setPosition(mouse_world_pos_);
    float dt_as_sec{dt.asSeconds()};

    player.update(dt_as_sec, mouse_screen_pos_);
    screen.main_view.setCenter(player.get_center());

    for (auto& zombie : horde.zombies)
        if (zombie && zombie->is_alive()) zombie->update(dt_as_sec, player.get_center());

    for (auto& bullet : weapon.bullets)
        if (bullet.is_flying()) bullet.update(dt_as_sec);

    for (auto& pickup : pickups)
        if (pickup) pickup->update(dt_as_sec);

    detect_collision(weapon, horde);
    detect_collision(player, horde);
    for (auto& pickup : pickups) detect_collision(player, pickup, weapon);
}

void Game::detect_collision(Weapon& weapon, Horde& horde) {
    for (auto& bullet : weapon.bullets) {
        // Was any zombie shot
        for (auto& zombie : horde.zombies) {
            if (zombie && zombie->is_alive() && bullet.is_flying()) {
                if (bullet.get_position().intersects(zombie->get_position())) {
                    bullet.stop();
                    if (zombie->hit()) {
                        score_ += 10;
                        if (score_ >= high_score_) high_score_ = score_;
                        if (--(horde.num_zombies_alive) == 0) set_state(State::LEVEL_UP);
                    }
                }
            }
        }
    }
}

void Game::detect_collision(Player& player, Horde& horde) {
    // Was player touched by zombie
    for (auto& zombie : horde.zombies) {
        if (zombie && zombie->is_alive() &&
            player.get_position().intersects(zombie->get_position())) {
            if (player.hit(game_time_total_)) { /*More here later*/
            }
            if (player.get_health() <= 0) set_state(State::GAME_OVER);
        }
    }
}

void Game::detect_collision(Player& player, Pickup* pickup, Weapon& weapon) {
    if (not pickup) return;
    // Has the player touched the pickup
    if (pickup->is_spawned() && player.get_position().intersects(pickup->get_position())) {
        switch (pickup->get_type()) {
            case PickupType::HEALTH: player.increase_health(pickup->got_it()); break;
            case PickupType::AMMO: weapon.bullets_spare += pickup->got_it(); break;
        }
    }
}
} // namespace game