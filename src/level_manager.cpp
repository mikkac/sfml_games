#include "level_manager.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace game
{
void Level::find_out_size() {
    std::ifstream input_file{path_to_file};
    std::string content;

    while (getline(input_file, content)) ++(size.y);
    size.x = content.length();

    input_file.close();
}

void Level::create_array() {
    std::ifstream input_file{path_to_file};
    try {
        array_level = new int*[size.y];
        for (unsigned idx = 0; idx < size.y; ++idx) array_level[idx] = new int[size.x];
    } catch (std::bad_alloc& error) {
        std::cerr << error.what();
        array_level = nullptr;
        return;
    }

    std::string row{};
    int y{};

    while (getline(input_file, row)) {
        for (unsigned x = 0; x < row.length(); ++x) array_level[y][x] = atoi(&(row[x]));
        ++y;
    }
    input_file.close();
}

void Level::delete_array() {
    if (array_level) {
        for (unsigned idx = 0; idx < kNumLevels; ++idx) delete[] array_level[idx];
        delete[] array_level;
        array_level = nullptr;
    }
}

void LevelManager::create_level(unsigned index) {
    switch (index) {
        case 1:
            level_.path_to_file = "res/levels/levels1.txt";
            level_.start_pos = Vector2f(100.f, 100.f);
            level_.base_time_limit = 30.f;
            break;
        case 2:
            level_.path_to_file = "res/levels/levels2.txt";
            level_.start_pos = Vector2f(100.f, 3600.f);
            level_.base_time_limit = 100.f;
            break;

        case 3:
            level_.path_to_file = "res/levels/levels3.txt";
            level_.start_pos = Vector2f(1250.f, 0.f);
            level_.base_time_limit = 30.f;
            break;

        case 4:
            level_.path_to_file = "res/levels/levels4.txt";
            level_.start_pos = Vector2f(50.f, 200.f);
            level_.base_time_limit = 50.f;
            break;
    }
    level_.find_out_size();
    level_.create_array();
}

void LevelManager::prepare_vertex_array() {
    vert_arr_.setPrimitiveType(Quads);
    vert_arr_.resize(level_.size.x * level_.size.y * kVertsInQuad);

    int current_vertex{0};

    for (unsigned x = 0; x < level_.size.x; ++x) {
        for (unsigned y = 0; y < level_.size.y; ++y) {
            // Position each vertex in the current quad
            vert_arr_[current_vertex + 0].position = Vector2f(x * kTileSize, y * kTileSize);
            vert_arr_[current_vertex + 1].position =
                Vector2f((x * kTileSize) + kTileSize, y * kTileSize);
            vert_arr_[current_vertex + 2].position =
                Vector2f((x * kTileSize) + kTileSize, (y * kTileSize) + kTileSize);
            vert_arr_[current_vertex + 3].position =
                Vector2f(x * kTileSize, (y * kTileSize) + kTileSize);

            // Which tile from the sprite sheet should be used
            unsigned vertical_offset{level_.array_level[y][x] * kTileSize};

            vert_arr_[current_vertex + 0].texCoords = Vector2f(0, 0 + vertical_offset);
            vert_arr_[current_vertex + 1].texCoords = Vector2f(kTileSize, 0 + vertical_offset);
            vert_arr_[current_vertex + 2].texCoords =
                Vector2f(kTileSize, kTileSize + vertical_offset);
            vert_arr_[current_vertex + 3].texCoords = Vector2f(0, kTileSize + vertical_offset);

            current_vertex += kVertsInQuad;
        }
    }
}

void LevelManager::load_next_level() {
    if (++current_level_ > kNumLevels) {
        current_level_ = 1;
        time_modifier_ -= 0.1f;
    }
    create_level(current_level_);
    prepare_vertex_array();
}

void LevelManager::delete_current_level() {
    level_.delete_array();
}
} // namespace game
