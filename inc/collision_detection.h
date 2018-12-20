#pragma once
#include "playable_character.h"

namespace game
{
class CollisionDetection
{
  public:
    bool detect(const LevelManager& lvl_man, PlayableCharacter& character);

  private:
    void create_collision_zone();
    void handle_leaving_level();
    void regular_block();
    void fire_and_water_block();
    bool endgame_block();

  private:
    LevelManager* level_manager_{nullptr};
    PlayableCharacter* character_{nullptr};
    Vector2i start_zone_{};
    Vector2i end_zone_{};
};
} // namespace game
