#pragma once
#include <SFML/Audio.hpp>

namespace game
{
using namespace sf;

enum class BufferType { FIRE, FALL_IN_FIRE, FALL_IN_WATER, JUMP, REACH_GOAL };
enum class SoundType { FIRE1, FIRE2, FIRE3, FALL_IN_FIRE, FALL_IN_WATER, JUMP, REACH_GOAL };

class SoundManager
{
  public:
    SoundManager();
    void play_fire(const Vector2f& emitter_pos, const Vector2f& listener_pos);
    void play_fall_in_fire();
    void play_fall_in_water();
    void play_jump();
    void play_reach_goal();

  private:
    Sound create_sound(const std::string& path, BufferType type);

  private:
    Sound sounds_[7];
    SoundBuffer buffers_[5];
    unsigned next_sound{1};
};

} // namespace game
