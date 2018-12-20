#pragma once
#include "playable_character.h"
#include "level_manager.h"
#include "engine.h" //TODO move all global constats to utils.h
namespace game
{
enum class BlockType { INVISIBLE, REGULAR, FIRE, WATER, ENDGAME };

class CollisionDetection
{
  public:
    bool detect(LevelManager* level_manager, PlayableCharacter* character);

  private:
    void create_collision_zone();
    void handle_leaving_level();
    void set_current_block(const Vector2i coords);
    void regular_block();
    void fire_and_water_block();
    bool endgame_block();

  private:
    LevelManager* level_manager_{nullptr};
    PlayableCharacter* character_{nullptr};
    FloatRect current_block_{0.f, 0.f, kTileSize, kTileSize};
    BlockType current_block_type_{};
    Vector2i start_zone_{};
    Vector2i end_zone_{};
};
} // namespace game
