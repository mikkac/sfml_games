#include "pch.h"
#include <SFML/Graphics.hpp>

const int WIDTH = 1920;
const int HEIGHT = 1080;
using namespace sf;
int main()
{
	//Create window
	VideoMode vm(WIDTH, HEIGHT);
	RenderWindow window(vm, "Timber", Style::Fullscreen);

	//Create background texture and sprite
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/Background.png");

	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	//Create tree texture and sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");

	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	//Create bee texture and sprite
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");

	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	//Is bee currently moving?
	bool beeActive = false;

	//How fast can bee fly
	float beeSpeed = 0.0f;

	//Create clouds textures and sprites
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");

	Sprite spriteCloud[3];

	for (unsigned short index = 0; index < 3; ++index)
	{
		spriteCloud[index].setTexture(textureCloud);
		spriteCloud[index].setPosition(index * 400, 0);
	}

	bool cloudActive[3]{ false };
	float cloudSpeed[3]{0.0f};

	Clock clock;
	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		// clear everything from the last frame
		window.clear();

		// draw, update scene
		window.draw(spriteBackground);
		window.draw(spriteTree);
		window.draw(spriteBee);

		Time dt = clock.restart();



		for (unsigned short index = 0; index < 3; ++index)
		{
			window.draw(spriteCloud[index]);
		}

		window.display();
	}
	return 0;
}

