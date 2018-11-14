#pragma once
#include "utils.h"
namespace game
{
class World
{
public:
    World(sf::Vector2f resolution, sf::IntRect mArena, int mTileSize);

private:
    sf::Vector2f mResolution;
    sf::IntRect mArena;
    int mTileSize;
};

}  // namespace game