#pragma once
#include <SFML/Graphics.hpp>

namespace timber {

class Rules;

class Game
{
private:
    Game(sf::Window window, std::vector<Drawing> drawings, Rules rules);
    Game() = delete; //disable possibility to create dummy game object
    Game(const Game& other) = default;
    Game& operator=(const Game& other) = default;
    Game(Game&& other) = default;
    Game& operator=(Game&& other) = default
public:
    static Game& createGame(sf::Window window, Rules rules);
    //methods
    float getTimeRemaining() const;
    float getScore() const;

    void setTimeRemaining(float newTimeRemaining);
    void increaseScore(int scorePerChop);

    void restart();
    void update();
private:
    sf::Window m_window;
    std::vector<Drawing> m_drawings;
    Rules rules;

    float m_timeRemaining;
    int m_score;
};

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

} //namespace timber
