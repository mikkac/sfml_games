#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace game
{
using namespace sf;

struct Level {
    std::string path_to_file{};
    Vector2u size{};
    Vector2f start_pos{};
    float base_time_limit{};

    int** load_from_file();

  private:
    Vector2u find_out_size(std::ifstream& input_file);
    int** create_array(std::ifstream& input_file);
};

Level load_level(unsigned index);

class LevelManager
{
  public:
    int** next_level(VertexArray& vert_arr);

    Vector2u get_level_size() const { return level_.size; }
    Vector2f get_start_pos() const { return level_.start_pos; }
    float get_time_limit() const { return level_.base_time_limit; }
    int get_current_level() const { return current_level_; }

  private:
    const unsigned kTileSize{50};
    const unsigned kVertsInQuad{4};
    const unsigned kNumLevels{4};

    Level level_;
    float time_modifier_{1.f};
    unsigned current_level_{0};
};
} // namespace game
