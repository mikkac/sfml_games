#pragma once
#include "playable_character.h"

namespace game
{
class Thomas : public PlayableCharacter
{
  public:
    Thomas();
    virtual bool handle_input() override;
};
} // namespace game
