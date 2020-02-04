#pragma once
#include "bullet.h"
#include "game.h"
#include "player.h"
#include "rectangle.h"
#include "text_wrapper.h"
#include "zombie.h"
#include <SFML/Graphics.hpp>

namespace game
{
using namespace sf;
const std::string level_up{
    "\n1- Increase rate of fire\
        \n2- Increase clip size (next reload)\
        \n3- Increase max health\
        \n4- Increase run speed\
        \n5- More and better health pickups\
        \n6- More and better ammo pickups"};

struct HudContent {
    HudContent();
    Font font;
    Sprite sprite_game_over{Sprite(holder.get_texture("res/graphics/background.png"))};
    Sprite sprite_ammo_icon{Sprite(holder.get_texture("res/graphics/ammo_icon.png"))};
    TextWrapper text_paused{"Press Enter \n to continue", font, 155, Color::White, Vector2f(400.f, 400.f)};
    TextWrapper text_game_over{"Press Enter to play", font, 125, Color::White, Vector2f(250.f, 850.f)};
    TextWrapper text_level_up{level_up, font, 80, Color::White, Vector2f(150.f, 250.f)};
    TextWrapper text_ammo{"", font, 55, Color::White, Vector2f(200.f, 980.f)};
    TextWrapper text_score{"Score: ", font, 55, Color::White, Vector2f(20.f, 0.f)};
    TextWrapper text_high_score{"High score: ", font, 55, Color::White, Vector2f(1400.f, 0.f)};
    TextWrapper text_zombies_remaining{"Zombies: ", font, 55, Color::White, Vector2f(1500.f, 980.f)};
    TextWrapper text_wave_number{"Wave: 0", font, 55, Color::White, Vector2f(1250.f, 980.f)};
    Rectangle health_bar{Vector2f(0.f, 0.f), Vector2f(450.f, 980.f), Color::Red};
};

class Hud
{
  public:
    Hud() = default;
    void update(const Player& player, const Weapon& weapon, const Horde& horde);
    HudContent get_content() const { return content; }

  public:
    HudContent content{};
    unsigned frames_since_last_hud_update_{};
    unsigned fps_measurement_frame_interval_{1000};

  private:
    void update_scores();
    void update_health_bar(const Player& player);
    void update_ammo(const Weapon& weapon);
    void update_horde(const Horde& horde);
};
} // namespace game
