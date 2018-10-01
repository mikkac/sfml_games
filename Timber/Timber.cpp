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

		//Move the bee
		if (!beeActive)
		{
			//how fast is the bee
			srand((int)time(0));
			beeSpeed = (rand() % 100) + 200;

			//how high is the bee
			srand((int)time(0) * 10);
			float height = rand() % 1350;
			spriteBee.setPosition(2000, height);
			beeActive = true;
		}
		else
		{
			spriteBee.setPosition(
				spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
				spriteBee.getPosition().y
			);

			if (spriteBee.getPosition().x < 0)
				beeActive = false;
		}

		//Manage the clouds
		for (unsigned short index = 0; index < 3; ++index)
		{
			if (!cloudActive[index])
			{
				//how fast is the cloud
				srand((int)time(0) * 10);
				cloudSpeed[index] = rand() % 200 + index * rand() % 200;

				//how high is the cloud
				srand((int)time(0) * 10);
				float height = (rand() % 75) + index * rand() % 200 ;
				spriteCloud[index].setPosition(index * rand() % 1000, height);
				cloudActive[index] = true;
			}
			else
			{
				spriteCloud[index].setPosition(
					spriteCloud[index].getPosition().x + (cloudSpeed[index] * dt.asSeconds()),
					spriteCloud[index].getPosition().y
				);

				if (spriteCloud[index].getPosition().x > 1920)
					cloudActive[index] = false;
			}
		}

		for (unsigned short index = 0; index < 3; ++index)
		{
			window.draw(spriteCloud[index]);
		}

		window.display();
	}
	return 0;
}

