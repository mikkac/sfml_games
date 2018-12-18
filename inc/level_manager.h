#pragma once
#include "texture_holder.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace game
{
using namespace sf;

const unsigned kTileSize{50};
const unsigned kVertsInQuad{4};
const unsigned kNumLevels{4};

struct Level {
    void find_out_size();
    void create_array();
    void delete_array();

    std::string path_to_file{};
    Vector2u size{};
    Vector2f start_pos{};
    float base_time_limit{};
    int** array_level{nullptr};
};

class LevelManager
{
  public:
    LevelManager() {}

    void load_next_level();
    void delete_current_level();

    VertexArray get_vertex_array() const { return vert_arr_; }
    int** get_array_level() const { return level_.array_level; }
    Texture& get_texture_tiles() const { return texture_tiles_; }
    Vector2u get_level_size() const { return level_.size; }
    Vector2f get_start_pos() const { return level_.start_pos; }
    float get_time_limit() const { return level_.base_time_limit * time_modifier_; }
    int get_current_level() const { return current_level_; }

  private:
    void create_level(unsigned index);
    void prepare_vertex_array();

  private:
    Level level_{};
    VertexArray vert_arr_{};
    Texture& texture_tiles_{
        TextureHolder::get_instance().get_texture("res/graphics/tiles_sheet.png")};

    float time_modifier_{0.9f};
    unsigned current_level_{0};
};
} // namespace game
