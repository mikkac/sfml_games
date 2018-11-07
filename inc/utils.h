#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
namespace timber 
{

template<typename T>
T createBuffer(const char* pathToFile)
{
    T buffer;
    buffer.loadFromFile(pathToFile);
    return buffer;
}


//Constants --------------------------------------------------------------------------------
constexpr int WIDTH{ 1920 };
constexpr int HEIGHT{ 1080 };
constexpr int HIDDEN_X { WIDTH + 300 };
constexpr int HIDDEN_Y { HEIGHT + 300 };
constexpr int NUM_BRANCHES{ 6 };
constexpr int NUM_CLOUDS{ 3 };
constexpr float AXE_POSITION_LEFT{ 700 };
constexpr float AXE_POSITION_RIGHT{ 1075 };
//------------------------------------------------------------------------------------------

enum Objects
{
    BACKGROUND = 0,
    TREE,
    LOG,
    BRANCH,
    CLOUDS = 3 + NUM_BRANCHES,
    BEE = 3 + NUM_BRANCHES + NUM_CLOUDS,
    PLAYER,
    GRAVESTONE,
    AXE 
};

enum class Side
{
    NONE, LEFT, RIGHT
};


struct vec2
{
    float x, y;
};

} //namespace timber