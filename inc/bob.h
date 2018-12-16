#pragma once
#include "playable_character.h"

namespace game
{
class Bob : public PlayableCharacter
{
  public:
    Bob();
    virtual bool handle_input() override;
};
} // namespace game
