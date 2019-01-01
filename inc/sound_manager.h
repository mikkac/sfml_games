#pragma once
#include <SFML/Audio.hpp>

namespace game
{
using namespace sf;

enum class SoundType { FIRE, FALL_IN_FIRE, FALL_IN_WATER, JUMP, REACH_GOAL };

class SoundManager
{
  public:
    SoundManager();
    void play_fire(const Vector2f& emitter_pos, const Vector2f& listener_pos);
    void play_sound(SoundType type);
  private:
    Sound create_sound(const std::string& path, SoundType type);
    bool is_buffer_loaded(SoundType type) const;

  private:
    Sound sounds_[5]{
        create_sound("res/sound/fire1.wav", SoundType::FIRE),
        create_sound("res/sound/fallinfire.wav", SoundType::FALL_IN_FIRE),
        create_sound("res/sound/fallinwater.wav", SoundType::FALL_IN_WATER),
        create_sound("res/sound/jump.wav", SoundType::JUMP),
        create_sound("res/sound/reachgoal.wav", SoundType::REACH_GOAL),
    };
    SoundBuffer buffers_[5]{};
};

} // namespace game
