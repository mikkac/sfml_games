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
    static SoundManager& get_instance(); 

    SoundManager(const SoundManager& other) = delete;
    SoundManager& operator=(const SoundManager& other) = delete;

    void play_fire(const Vector2f& emitter_pos, const Vector2f& listener_pos);
    void play_sound(SoundType type);
  private:
    Sound create_sound(const std::string& path, SoundType type);
    bool is_buffer_loaded(SoundType type) const;

  private:
    Sound sounds_[5];
    SoundBuffer buffers_[5];
};

} // namespace game
