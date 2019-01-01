#include "sound_manager.h"

namespace game
{
SoundManager::SoundManager() {
    float min_distance{150.f};
    float attenuation{15.f};
    for (unsigned idx = 0; idx < 3; ++idx) {
        sounds_[idx].setAttenuation(attenuation);
        sounds_[idx].setMinDistance(min_distance);
        sounds_[idx].setLoop(true);
    }
}

void SoundManager::play_fire(const Vector2f& emitter_pos, const Vector2f& listener_pos) {
    Listener::setPosition(listener_pos.x, listener_pos.y, 0.f);

    Sound& sound = sounds_[static_cast<int>(SoundType::FIRE)];
    sound.setPosition(emitter_pos.x, emitter_pos.y, 0.f);

    if (sound.getStatus() == Sound::Status::Stopped) sound.play();
}

void SoundManager::play_sound(SoundType type) {
    sounds_[static_cast<int>(type)].setRelativeToListener(true);
    sounds_[static_cast<int>(type)].play();
}

Sound SoundManager::create_sound(const std::string& path, SoundType type) {
    if (not is_buffer_loaded(type)) buffers_[static_cast<int>(type)].loadFromFile(path);
    return Sound{buffers_[static_cast<int>(type)]};
}

bool SoundManager::is_buffer_loaded(SoundType type) const {
    if (buffers_[static_cast<int>(type)].getDuration() == Time::Zero) return false;
}
} // namespace game
