#pragma once
#include "drawing.h"

namespace timber
{
void handleInput(sf::Keyboard key);
class Rules
{
public:
    Rules(float timeOnStart, float timePerChop, float scorePerChop);
    float getTimeOnStart() const;
    float getTimePerChop() const;
    float getScorePerChop() const;

    void setTimePerChop(float newTimePerChop);

private:
    float mTimeOnStart;
    float mTimePerChop;
    float mScorePerChop;
};

class Game
{
public:
    Game(Rules rules);
    // methods
    bool isPaused() const;
    void setPaused(bool isPaused);

    float getTimeRemaining() const;
    float getScore() const;

    void setTimeRemaining(float newTimeRemaining);
    void setScore(int newScore);
    void increaseScore();

    void restart();

    Rules rules;

private:
    float mTimeRemaining;
    int mScore;
    bool mPaused;
};

}  // namespace timber
