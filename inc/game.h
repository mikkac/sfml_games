#pragma once
#include "bullet.h"
#include "pickup.h"
#include "player.h"
#include "screen.h"
#include "zombie.h"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace game
{
enum class State { PAUSE, LEVEL_UP, GAME_OVER, PLAY };

class Game
{
  public:
    Game() : state_{State::GAME_OVER} {}
    void set_state(State state) { state_ = state; }
    bool pause() const { return state_ == State::PAUSE; }
    bool level_up() const { return state_ == State::LEVEL_UP; }
    bool game_over() const { return state_ == State::GAME_OVER; }
    bool play() const { return state_ == State::PLAY; }
    void update(Clock& clock, Screen& screen, Player& player, std::vector<Zombie*>& zombies,
                Weapon& weapon, std::vector<Pickup*>& pickups);

    void detect_collision(Bullet* bullets, std::vector<Zombie*>& zombies);

    const State& get_state() const { return state_; }
    Time get_time_total() const { return game_time_total_; }
    Vector2f get_mouse_world_pos() const { return mouse_world_pos_; }

  private:
    State state_;
    Vector2f mouse_world_pos_{};
    Vector2i mouse_screen_pos_{};
    Time game_time_total_;
    int score_{};
    int high_score_{};
};
} // namespace game