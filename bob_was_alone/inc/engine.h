#pragma once
#include "collision_detection.h"
#include "hud.h"
#include "level_manager.h"
#include "particle_system.h"
#include "playable_character.h"
#include "sound_manager.h"
#include "texture_holder.h"
#include "utils.h"
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
    Clock clock{};
    float remaining{10.f};
    Time game_total{Time::Zero};
};

struct Screen {
    Screen();

    RenderWindow window{};
    Views views{};
    Sprite background_sprite{};
    Texture background_texture;
    Shader ripple_shader;
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

    void draw_split_screen();
    void draw_main_scrren();
    void draw_hud();

    bool detect_movement(PlayableCharacter* character);
    void detect_characters_overlaping();

    void populate_emitters();

  private:
    Screen screen_;
    Hud hud_;
    TimeWrapper time_;
    LevelManager level_manager_;
    CollisionDetection collision_;
    ParticleSystem particle_system_;

    Thomas thomas_;
    Bob bob_;

    std::vector<Vector2f> fire_emitters_{};

    bool playing_{false};
    bool character_focus_{true}; // main view foucs- TRUE: Thomas, FALSE: Bob
    bool split_screen_{false};
    bool new_level_required_{true};
};
} // namespace game

