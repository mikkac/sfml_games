#pragma once
#include "texture_holder.h"
#include <SFML/Graphics.hpp>
namespace game
{
using namespace sf;

struct Views {
    View main, left, right;     // main views
    View bg_main, bg_left, bg_right; // background views
    View hud;
};

class Engine
{
  public:
    Engine();
    void run();

  private:
    void input();
    void update(float dt_as_seconds);
    void draw();

  private:
    const int kTileSize{50};
    const int kVertsInQuad{4};
    const int kGravity{300};

    RenderWindow window_;

    Views views_;

    Sprite background_sprite_;
    Texture background_texture_;

    bool playing_{false};
    bool character_one_{true}; // is character 1 or 2 the current focus
    bool split_screen_{false};

    float time_remaining_{10.f};
    Time game_total_time_{Time::ZERO};

    bool new_level_required_{true};
};
} // namespace game

