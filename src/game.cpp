#include "game.h"

namespace timber
{

// Game class' cstor and methods -------------------------------------------------------------------
Game::Game(Rules rules)
    : mScore{ 0 }, rules{ rules }
{
    mTimeRemaining = rules.getTimeOnStart();
}

bool Game::isPaused() const
{
    return mPaused;
}

void Game::setPaused(bool isPaused)
{
    mPaused = isPaused;
}

float Game::getTimeRemaining() const
{
    return mTimeRemaining;
}

float Game::getScore() const
{
    return mScore;
}

void Game::setTimeRemaining(float newTimeRemaining)
{
    mTimeRemaining = newTimeRemaining;
}

void Game::setScore(int newScore)
{
    mScore = newScore;
}

void Game::increaseScore()
{
    setScore(mScore + rules.getScorePerChop());
}

void Game::restart()
{
    mTimeRemaining = rules.getTimeOnStart();
    mScore = 0;
}

// Rules class' cstor and methods ------------------------------------------------------------------
Rules::Rules(float timeOnStart, float timePerChop, float scorePerChop)
    : mTimeOnStart{ timeOnStart },
      mTimePerChop{ timePerChop },
      mScorePerChop{ scorePerChop }
{
}

float Rules::getTimeOnStart() const
{
    return mTimeOnStart;
}

float Rules::getTimePerChop() const
{
    return mTimePerChop;
}

float Rules::getScorePerChop() const
{
    return mScorePerChop;
}

void Rules::setTimePerChop(float newTimePerChop)
{
    mTimePerChop = newTimePerChop;
}

} //namespace timber
