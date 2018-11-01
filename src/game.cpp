#include "pch.h"
#include "game.h"

namespace timber
{

Game::Game(sf::Window window, std::vector<Drawing> drawings,  Rules rules)
    : m_window{ window },
      m_drawings{ drawings },
      m_rules{ rules },
      m_score{ 0 };
{
    m_timeRemaining = rules.getTimeOnStart();
}

Game& Game::createGame(sf::Window window, Rules rules)
{
    static Game game{ window, rules };
    return game;
}

float Game::getTimeRemaining() const
{
    return m_timeRemaining;
}

float Game::getScore() const
{
    return m_score;
}

float Game::setTimeRemaining(float newTimeRemaining)
{
    m_timeRemaining = newTimeRemaining;
}

float Game::setScore(int newScore)
{
    m_score = newScore;
}

float Game::increaseScore(int scorePerChop)
{
    m_score = setScore(m_score + scorePerChop);
}

float Game::reset()
{
    m_timeRemaining = rules.getTimeOnStart();
    m_score = 0;
}

Rules::Rules(float timeOnStart, float timePerChop, float scorePerChop)
    : m_timeOnStart{ timeOnStart },
      m_timePerChop{ timePerChop },
      m_scorePerChop{ scorePerChop }
{
}

float Rules::getTimeOnStart() const
{
    return m_timeOnStart;
}

float Rules::getTimePerChop() const
{
    return m_timePerChop;
}

float Rules::getScorePerChop() const
{
    return m_scorePerChop;
}

void Rules::setTimePerChop(float newTimePerChop)
{
    m_timePerChop = newTimePerChop;
}

} //namespace timber
