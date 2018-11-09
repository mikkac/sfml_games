#include "utils.h"
namespace timber
{
// Buffers -----------------------------------------------------------------------------------
sf::Texture textureBackground = createBuffer<sf::Texture>("res/graphics/background.png");
sf::Texture textureBee = createBuffer<sf::Texture>("res/graphics/bee.png");
sf::Texture textureCloud = createBuffer<sf::Texture>("res/graphics/cloud.png");
sf::Texture textureTree = createBuffer<sf::Texture>("res/graphics/tree.png");
sf::Texture textureBranch = createBuffer<sf::Texture>("res/graphics/branch.png");
sf::Texture textureLog = createBuffer<sf::Texture>("res/graphics/log.png");
sf::Texture textureAxe = createBuffer<sf::Texture>("res/graphics/axe.png");
sf::Texture texturePlayer = createBuffer<sf::Texture>("res/graphics/player.png");
sf::Texture textureGravestone = createBuffer<sf::Texture>("res/graphics/rip.png");

sf::SoundBuffer soundBufferChop = createBuffer<sf::SoundBuffer>("res/sound/chop.wav");
sf::SoundBuffer soundBufferDeath = createBuffer<sf::SoundBuffer>("res/sound/death.wav");
sf::SoundBuffer soundBufferOutOfTime = createBuffer<sf::SoundBuffer>("res/sound/out_of_time.wav");

sf::Font font = createBuffer<sf::Font>("res/fonts/KOMIKAP_.ttf");
//-------------------------------------------------------------------------------------------

// Rest of global variables ----------------------------------------------------------------
Random rand_num;
//------------------------------------------------------------------------------------------

}  // namespace timber