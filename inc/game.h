#pragma once
#include "drawing.h"

namespace timber {

using Drawings = std::vector<Drawing*>;
using Sounds = std::vector<Sound*>;

class Rules 
{
public:
    Rules(float timeOnStart, float timePerChop, float scorePerChop);
    float getTimeOnStart() const;
    float getTimePerChop() const;
    float getScorePerChop() const;

    void setTimePerChop(float newTimePerChop);
private:
    float m_timeOnStart;
    float m_timePerChop;
    float m_scorePerChop;
};


class Game
{
private:
    Game(sf::Window& window, Drawings drawings, Sounds sounds, Rules rules);
    Game() = delete; //disable possibility to create dummy game object
    Game(const Game& other) = default;
    Game& operator=(const Game& other) = default;
    Game(Game&& other) = default;
    Game& operator=(Game&& other) = default;
public:
    static Game& createGame(sf::Window& window, Drawings drawings, Sounds sounds, Rules rules);
    //methods
    float getTimeRemaining() const;
    float getScore() const;

    void setTimeRemaining(float newTimeRemaining);
    void setScore(int newScore);
    void increaseScore(int scorePerChop);

    void restart();
    void update();
private:
    sf::Window& m_window;
    Drawings m_drawings;
    Sounds m_sounds;
    Rules m_rules;

    float m_timeRemaining;
    int m_score;
};

} //namespace timber
