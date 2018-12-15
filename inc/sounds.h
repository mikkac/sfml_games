#pragma once
#include <SFML/Audio.hpp>
#include <string>

namespace game
{
using namespace sf;


enum class AudioType { HIT = 0, SPLAT, SHOOT, RELOAD, RELOAD_FAILED, POWERUP, PICKUP };

class Sounds
{
  public:
    Sounds() = default;
    Sounds(const Sounds& other) = delete;
    Sounds& operator=(const Sounds& other) = delete;

    static Sounds& get_instance();
    Sound create_sound(const std::string& path, AudioType type);

    Sound& get_sound(AudioType type) { return sounds_[static_cast<int>(type)]; }

  private:
    SoundBuffer buffers_[7];
    Sound sounds_[7]{create_sound("res/sound/hit.wav", AudioType::HIT),
                     create_sound("res/sound/splat.wav", AudioType::SPLAT),
                     create_sound("res/sound/shoot.wav", AudioType::SHOOT),
                     create_sound("res/sound/reload.wav", AudioType::RELOAD),
                     create_sound("res/sound/reload_failed.wav", AudioType::RELOAD_FAILED),
                     create_sound("res/sound/powerup.wav", AudioType::POWERUP),
                     create_sound("res/sound/pickup.wav", AudioType::PICKUP)};
};
} // namespace game
