#pragma once
#include "bob.h"
#include "texture_holder.h"
#include "thomas.h"
#include "level_manager.h"
#include <SFML/Graphics.hpp>
namespace game
{
using namespace sf;

struct Views {
    Views() = default;
    Views(const Vector2f& resolution);

    View main, left, right;          // main views
    View bg_main, bg_left, bg_right; // background views
    View hud;
};

struct TimeWrapper {
    Clock clock;
    float remaining{10.f};
    Time game_total{Time::Zero};
};

struct Screen {
    Views views;
    Sprite background_sprite_;
    Texture background_texture_;
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
    void load_level();

  private:
    const int kTileSize{50};
    const int kVertsInQuad{4};
    const int kGravity{300};

    RenderWindow window_;
    LevelManager level_manager_;
    Views views_;
    Sprite background_sprite_;
    Texture background_texture_;

    Thomas thomas_;
    Bob bob_;

    bool playing_{false};
    bool character_one_{true}; // is character 1 or 2 the current focus
    bool split_screen_{false};

    TimeWrapper time_;

    bool new_level_required_{true};
};
} // namespace game

