#include "hud.h"
#include <iostream>

namespace game
{
HudContent::HudContent() {
    font.loadFromFile("res/fonts/zombiecontrol.ttf");
    sprite_game_over.setPosition(0.f, 0.f);
    sprite_ammo_icon.setPosition(20.f, 980.f);
}

void Hud::update(const Player& player, const Weapon& weapon, const Horde& horde) {
    if (++frames_since_last_hud_update_ > fps_measurement_frame_interval_) {
        update_scores();
        update_health_bar(player);
        update_ammo(weapon);
        update_horde(horde);
        frames_since_last_hud_update_ = 0;
    }
}

void Hud::update_health_bar(const Player& player) {
    content_.health_bar.set_size(Vector2f(player.get_health() * 3.f, 50.f));
}

void Hud::update_ammo(const Weapon& weapon) {
    std::stringstream stream_ammo;

    stream_ammo << weapon.bullets_in_clip << "/" << weapon.bullets_spare;
    content_.text_ammo.set_string(stream_ammo.str());
}

void Hud::update_scores() {
    std::stringstream stream_score;
    std::stringstream stream_high_score;

    stream_score << "Score: " << Score::get_instance().get_score();
    std::cout << Score::get_instance().get_score();
    content_.text_score.set_string(stream_score.str());

    stream_high_score << "High score: " << Score::get_instance().get_high_score();
    content_.text_high_score.set_string(stream_high_score.str());
}

void Hud::update_horde(const Horde& horde) {
    std::stringstream stream_wave;
    std::stringstream stream_zombies_alive;

    stream_wave << "Wave: " << horde.wave_number;
    content_.text_wave_number.set_string(stream_wave.str());

    stream_zombies_alive << "Zombies: " << horde.num_zombies_alive;
    content_.text_zombies_remaining.set_string(stream_zombies_alive.str());
}
} // namespace game
