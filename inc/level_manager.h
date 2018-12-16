#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace game
{
using namespace sf;
using LevelMatrix = std::vector<std::vector<int>>;

class LevelManager
{
  public:
    LevelMatrix next_level(VertexArray& vert_arr);

    Vector2u get_level_size() const { return level_size_; }
    Vector2f get_start_pos() const { return start_pos; }
    float get_time_limit() const { return base_time_limit_; }
    int get_current_level() const { return current_level_; }

  private:
    const int kTileSize{50};
    const int kVertsInQuad{4};
    const int kNumLevels{4};

    Vector2u level_size_;
    Vector2f start_pos_;
    float time_modifier_{1.f};
    float base_time_limit_{0.f};
    unsigned current_level_{0};
};
} // namespace game
