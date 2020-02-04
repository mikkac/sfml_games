#pragma once

namespace game
{
class Score
{
  public:
    Score() = default;
    Score(const Score& other) = delete;
    Score& operator=(const Score& other) = delete;

    static Score& get_instance();

    void load_high_score();
    void save_high_score() const;
    void increase(int value) { score_ += value; }
    void update_high_score() { high_score_ = score_; }
    void reset() { score_ = 0; }
    int get_score() const { return score_; }
    int get_high_score() const { return high_score_; }

  private:
    int score_{};
    int high_score_{};
};
} // namespace game
