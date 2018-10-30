#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <sstream>

//Global constants
constexpr int WIDTH{ 1920 };
constexpr int HEIGHT{ 1080 };
constexpr int NUM_BRANCHES{ 6 };

enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

using namespace sf;

void updateBranches(int seed);

int main()
{
	//Create window
	VideoMode vm(WIDTH, HEIGHT);
	RenderWindow window(vm, "Timber", Style::Fullscreen);

	//Create background texture and sprite
	Texture textureBackground;
	textureBackground.loadFromFile("res/graphics/background.png");

	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	//Create tree texture and sprite
	Texture textureTree;
	textureTree.loadFromFile("res/graphics/tree.png");

	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	//Create bee texture and sprite
	Texture textureBee;
	textureBee.loadFromFile("res/graphics/bee.png");

	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	//Is bee currently moving?
	bool beeActive = false;

	//How fast can bee fly
	float beeSpeed = 0.0f;

	//Create clouds textures and sprites
	Texture textureCloud;
	textureCloud.loadFromFile("res/graphics/cloud.png");

	Sprite spriteCloud[5];

	for (unsigned short index = 0; index < 5; ++index)
	{
		spriteCloud[index].setTexture(textureCloud);
		spriteCloud[index].setPosition(index * 400, 0);
	}

	bool cloudActive[5]{ false };
	float cloudSpeed[5]{0.0f};

	//Create branches
	Texture textureBranch;
	textureBranch.loadFromFile("res/graphics/branch.png");
	Sprite branches[NUM_BRANCHES];

	for (unsigned idx = 0; idx < NUM_BRANCHES; ++idx)
	{
		branches[idx].setTexture(textureBranch);
		branches[idx].setPosition(-2000, 2000); // outside the screen
		//Set the sprite's origin to dead center
		branches[idx].setOrigin(220, 20);
	}

	//Prepare Player
	Texture texturePlayer;
	texturePlayer.loadFromFile("res/graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);

	//The Player starts on the left
	side playerSide{ side::LEFT };
	
	//Prepare the gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("res/graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 2000);

	//Prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("res/graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	//Line the axe up with the tree
	const float AXE_POSITION_LEFT{ 700 };
	const float AXE_POSITION_RIGHT{ 1075 };

	//Prepare flying log
	Texture textureLog;
	textureLog.loadFromFile("res/graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	//Log related variables
	bool logActive{ false };
	float logSpeedX{ 1000.f };
	float logSpeedY{ -1500.f };


	//Texts- score and startGame
	unsigned int score{};
	Text textMessage;
	Text textScore;
	//Load font
	Font font;
	font.loadFromFile("res/fonts/KOMIKAP_.ttf");
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

	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth{ 400.f };
	float timeBarHeight{ 80.f };
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition(WIDTH / 2 - timeBarStartWidth / 2, 980);

	Time gameTimeTotal{};
	float timeRemaining = 6.f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	//Track whether the game is started
	bool isStarted{ false };

	//Control the player input
	bool acceptInput{ false };

	//Prepare the sound
	SoundBuffer bufferChop;
	bufferChop.loadFromFile("res/sound/chop.wav");
	Sound soundChop;
	soundChop.setBuffer(bufferChop);

	SoundBuffer bufferDeath;
	bufferDeath.loadFromFile("res/sound/death.wav");
	Sound soundDeath;
	soundDeath.setBuffer(bufferDeath);

	SoundBuffer bufferOOT;
	bufferOOT.loadFromFile("res/sound/out_of_time.wav");
	Sound soundOOT;
	soundOOT.setBuffer(bufferOOT);	

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && isStarted)
			{
				//Listen for key press again
				acceptInput = true;

				//Hide the axe
				spriteAxe.setPosition(
					2000,
					spriteAxe.getPosition().y
				);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			isStarted = true;
			//Reset the time and the score
			score = 0;
			timeRemaining = 6.f;

			//Make all branches disappear
			for (unsigned idx = 0; idx < NUM_BRANCHES; ++idx)
				branchPositions[idx] = side::NONE;

			//Make sure gravestone is hidden
			spriteRIP.setPosition(675, 2000);

			//Move the player into position
			spritePlayer.setPosition(580, 720);

			acceptInput = true;
		}

		if (acceptInput)
		{
			//Handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				playerSide = side::RIGHT;
				++score;

				if (timeRemaining <= 6.0 && score > 0)
					timeRemaining += (2.0 / score) + 0.15;

				spriteAxe.setPosition(
					AXE_POSITION_RIGHT,
					spriteAxe.getPosition().y
				);

				spritePlayer.setPosition(1200, 720);

				updateBranches(score);

				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;

				//Update the score text
				std::stringstream ss;
				ss << "Score: " << score;
				textScore.setString(ss.str());

				//Play a chop sound
				soundChop.play();
			}

			//Handle pressing the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				playerSide = side::LEFT;
				++score;

				if(timeRemaining <= 6.0 && score > 0)
					timeRemaining += (2.0 / score) + 0.15;

				spriteAxe.setPosition(
					AXE_POSITION_LEFT,
					spriteAxe.getPosition().y
				);

				spritePlayer.setPosition(580, 720);

				updateBranches(score);

				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;

				//Update the score text
				std::stringstream ss;
				ss << "Score: " << score;
				textScore.setString(ss.str());

				//Play a chop sound
				soundChop.play();
			}
		}

		if (isStarted)
		{
			Time dt = clock.restart();

			//Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();
			//Resize the time bar
			timeBar.setSize(Vector2f(timeRemaining * timeBarWidthPerSecond, timeBarHeight));

			if (timeRemaining <= 0.f)
			{
				isStarted = false;
				textMessage.setString("Out of time!");

				//Reposition the text based on its new size
				FloatRect textRect = textMessage.getLocalBounds();
				textMessage.setOrigin(
					textRect.left + textRect.width / 2.f,
					textRect.top + textRect.height / 2.f
				);

				textMessage.setPosition(WIDTH / 2.f, HEIGHT / 2.f);

				//Play a OutOfTime sound
				soundOOT.play();
			}
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

			//Update branch sprites
			for (unsigned idx = 0; idx < NUM_BRANCHES; ++idx)
			{
				float height = idx * 150;
				switch (branchPositions[idx])
				{
				case side::LEFT:
					//Move the branch to the left side and rotate
					branches[idx].setPosition(610, height);
					branches[idx].setRotation(180);
					break;
				case side::RIGHT:
					//Move the branch to the right side and don't rotate
					branches[idx].setPosition(1330, height);
					branches[idx].setRotation(0);
					break;
				case side::NONE:
					//Hide the branch
					branches[idx].setPosition(3000, height);
					break;
				default:
					break;
				}
			}

			//Handle a flying log
			if (logActive)
			{
				spriteLog.setPosition(
					spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY * dt.asSeconds())
				);

				//Has the log reached the right or left edge of screen?
				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
				{
					//Set it up ready to be a whole new log next frame
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			//Has the player been squished by a branch
			if (branchPositions[5] == playerSide)
			{
				//Death
				isStarted = false;
				acceptInput = false;

				//Draw the gravestone
				spriteRIP.setPosition(
					spritePlayer.getPosition().x,
					800
				);

				//Hide the player and axe 
				spritePlayer.setPosition(2000, 660);
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);

				//Change the text of the message
				textMessage.setString("SQUISHED!");

				//Center it on the screen
				FloatRect textRect = textMessage.getLocalBounds();
				textMessage.setOrigin(
					textRect.left + textRect.width / 2.f,
					textRect.top + textRect.height / 2.f
				);

				textMessage.setPosition(WIDTH / 2.f, HEIGHT / 2.f);

				//Play a death sound
				soundDeath.play();
			}

		} //if(!isStarted)

		// clear everything from the last frame
		window.clear();

		// draw, update scene
		
		window.draw(spriteBackground);
		for (unsigned idx = 0; idx < NUM_BRANCHES; ++idx)
		{
			window.draw(branches[idx]);
		}

		window.draw(spriteTree);
		window.draw(spritePlayer);
		window.draw(spriteAxe);
		window.draw(spriteLog);
		window.draw(spriteRIP);

		window.draw(spriteBee);
		for (unsigned short index = 0; index < 5; ++index)
		{
			window.draw(spriteCloud[index]);
		}
		if (!isStarted)
			window.draw(textMessage);
		window.draw(textScore);
		window.draw(timeBar);
		window.display();
	}
	return 0;
}

void updateBranches(int seed)
{
	//Move all branches down one place
	for (unsigned idx = NUM_BRANCHES - 1; idx > 0; --idx)
 		branchPositions[idx] = branchPositions[idx - 1];

	//Spawn new branch at position 0
	srand((int)time(0) + seed);
	int random = rand() % 2;
	switch (random)
	{
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}

