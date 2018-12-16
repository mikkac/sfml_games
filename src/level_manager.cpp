#include "level_manager.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace game
{
Level load_level(unsigned index) {
    Level result{};
    std::string path_to_file{};
    switch (index) {
        case 1:
            result.path_to_file = "res/levels/levels1.txt";
            result.start_pos = Vector2f(100.f, 100.f);
            result.base_time_limit = 30.f;
            break;
        case 2:
            result.path_to_file = "res/levels/levels2.txt";
            result.start_pos = Vector2f(100.f, 3600.f);
            result.base_time_limit = 100.f;
            break;

        case 3:
            result.path_to_file = "res/levels/levels3.txt";
            result.start_pos = Vector2f(1250.f, 0.f);
            result.base_time_limit = 30.f;
            break;

        case 4:
            result.path_to_file = "res/levels/levels4.txt";
            result.start_pos = Vector2f(50.f, 200.f);
            result.base_time_limit = 50.f;
            break;
    }
    return result;
}

int** Level::load_from_file() {
    std::ifstream input_file{path_to_file};

    size = find_out_size(input_file);
    int** array_level = create_array(input_file);
    
    input_file.close();

    return array_level;
}

Vector2u Level::find_out_size(std::ifstream& input_file) {
    Vector2u result{};
    std::string content;

    input_file.clear();
    input_file.seekg(0, std::ios::beg);

    while (getline(input_file, content)) ++(result.y);
    result.x = content.length();
    return result;
}

int** Level::create_array(std::ifstream& input_file) {
    input_file.clear();
    input_file.seekg(0, std::ios::beg);
    int** array_level = nullptr;
    try {
        array_level = new int*[size.y];
        for (unsigned idx = 0; idx < size.y; ++idx) array_level[idx] = new int[size.x];
    } catch (std::exception& error) {
        std::cerr << error.what();
        return nullptr;
    }

    std::string row{};
    int y{};

    while(input_file >> row) {
        for(unsigned x = 0; x < row.length(); ++x) {
            const char value = row[x];
            array_level[y][x] = atoi(&value);
        }
        ++y;
    }
    return array_level;
}

int** LevelManager::next_level(VertexArray& vert_arr) {
    if (++current_level_ > kNumLevels) {
        current_level_ = 1;
        time_modifier_ -= 0.1f;
    }
    //TODO finish implementation
}
} // namespace game
