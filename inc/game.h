#pragma once
#include "player.h"
#include "screen.h"
#include <SFML/Graphics.hpp>

using namespace sf;

namespace game
{
enum class State { PAUSE, LEVEL_UP, GAME_OVER, PLAY };

class Game
{
  public:
    Game() : state_{State::GAME_OVER} {}
    const State& get_state() const { return state_; }
    void set_state(State state) { state_ = state; }
    bool pause() const { return state_ == State::PAUSE; }
    bool level_up() const { return state_ == State::LEVEL_UP; }
    bool game_over() const { return state_ == State::GAME_OVER; }
    bool play() const { return state_ == State::PLAY; }

    void update(Clock& clock, Screen& screen, Player& player);

  private:
    State state_;
    Vector2f mouse_world_pos_{};
    Vector2i mouse_screen_pos_{};
    Time game_time_total_;
};
} // namespace game