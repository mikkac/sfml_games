#include "pch.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <sstream>

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

	Sprite spriteCloud[5];

	for (unsigned short index = 0; index < 5; ++index)
	{
		spriteCloud[index].setTexture(textureCloud);
		spriteCloud[index].setPosition(index * 400, 0);
	}

	bool cloudActive[5]{ false };
	float cloudSpeed[5]{0.0f};

	//Texts- score and startGame
	unsigned int score{};
	Text textMessage;
	Text textScore;
	//Load font
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	//Set the font to our texts
	textMessage.setFont(font);
	textScore.setFont(font);
	
	//Set rest of text properties
	textMessage.setString("Press Enter to start");
	textScore.setString("Score: 0");
	textMessage.setCharacterSize(75);
	textScore.setCharacterSize(100);
	textMessage.setFillColor(Color::White);
	textScore.setFillColor(Color::White);

	//Position of text
	FloatRect textRect = textMessage.getLocalBounds();
	textMessage.setOrigin(
		textRect.left + textRect.width / 2.f,
		textRect.top + textRect.height / 2.f
	);

	textMessage.setPosition(WIDTH / 2.f, HEIGHT / 2.f);
	textScore.setPosition(20.f, 20.f);

	Clock clock;

	//Track whether the game is still running
	bool isStarted{ false };
	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();
		if (Keyboard::isKeyPressed(Keyboard::Return))
			isStarted = true;
		if (isStarted)
		{
			Time dt = clock.restart();

			//Move the bee
			if (!beeActive)
			{
				//how fast is the bee
				srand((int)time(0));
				beeSpeed = (rand() % 100) + 300;

				//how high is the bee
				srand((int)time(0) * 10);
				float height = rand() % 1000;
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
			for (unsigned short index = 0; index < 5; ++index)
			{
				if (!cloudActive[index])
				{
					//how fast is the cloud
					srand((int)time(0) * 10);
					cloudSpeed[index] = (rand() % 100 + index * rand() % 300) * pow(-1, index);

					//how high is the cloud
					srand((int)time(0) * 10);
					float height = (rand() % 75) + index * rand() % 200;
					spriteCloud[index].setPosition(rand() % 1000 + 500 * pow(-1, index), height);
					cloudActive[index] = true;
				}
				else
				{
					spriteCloud[index].setPosition(
						spriteCloud[index].getPosition().x + (cloudSpeed[index] * dt.asSeconds()),
						spriteCloud[index].getPosition().y
					);

					if (spriteCloud[index].getPosition().x > WIDTH || spriteCloud[index].getPosition().x < 0)
						cloudActive[index] = false;
				}
			}
			// Update the score text
			std::stringstream ss;
			ss << "Score: " << score;
			textScore.setString(ss.str());
		} //if(!isStarted)

		// clear everything from the last frame
		window.clear();

		// draw, update scene
		
		window.draw(spriteBackground);
		window.draw(spriteTree);
		window.draw(spriteBee);
		for (unsigned short index = 0; index < 5; ++index)
		{
			window.draw(spriteCloud[index]);
		}
		if (!isStarted)
			window.draw(textMessage);
		window.draw(textScore);
		window.display();
	}
	return 0;
}

