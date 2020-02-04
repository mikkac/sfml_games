#include "score.h"
#include <fstream>
namespace game
{
Score& Score::get_instance() {
    static Score instance;
    return instance;
}

void Score::load_high_score() {
    std::ifstream input_file{"res/gamedata/scores.txt"};
    if (input_file.is_open()) {
        input_file >> high_score_;
        input_file.close();
    } else {
        return;
    }
}

void Score::save_high_score() const {
    std::ofstream output_file{"res/gamedata/scores.txt"};
    if (output_file.is_open()) {
        output_file << high_score_;
        output_file.close();
    } else {
        return;
    }
}
} // namespace game
