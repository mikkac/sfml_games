//TODO flying log is not visible
//TODO gravestone should be a bit lower in y axis
//TODO weird behaviour of clouds
//TODO refactor texts and rectangles
//TODO why these buffers cannot be in utils.h
//TODO refactor code in general- it looks like shit


#include "game.h"
#include <memory>
#include <cmath>
#include <sstream>

using namespace timber;
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

using namespace sf;

//Buffers -----------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------

void updateBranches(std::vector<Branch>& branches, int seed);


int main()
{
	//Create game and rules
	Rules rules(6.0f, 0.15, 1.0f);
	Game game(rules);

	//Create window
	VideoMode vm(WIDTH, HEIGHT);
	RenderWindow window(vm, "Timber", Style::Fullscreen);

	//Create background
	Drawing background(window, textureBackground);
	Drawing tree(window, textureTree, vec2{ 810, 0 });
	
	// //Create bee
	Bee bee(window, textureBee);
	
	//Create clouds textures and sprites
	std::vector<Cloud> clouds(NUM_CLOUDS, Cloud(window, textureCloud, vec2{ HIDDEN_X, int(rand() % 300) }));
	
	//Create tree
	//Create branches
	std::vector<Branch> branches(NUM_BRANCHES, Branch(window, textureBranch, vec2{	HIDDEN_X, HIDDEN_Y }));
	for(auto& branch : branches)
	{	
		branch.setOrigin(220, 20);
	}

	//Prepare Player
	Player player(window, texturePlayer, textureGravestone, vec2{ 580, 720 });
	//The Player starts on the left
	player.setSide(Side::LEFT);
	
	//Prepare the axe
	Axe axe(window, textureAxe, vec2{ 700, 830 });

	//Prepare flying log
	Texture textureLog;
	Log log(window, textureLog, vec2{ 810, 720 }, vec2{ 1000.f, -1500.f});

// TODO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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
	float timeBarWidthPerSecond = timeBarStartWidth / game.getTimeRemaining();

	// //Track whether the game is started
	// bool isStarted{ false };

	//Control the player input
	bool acceptInput{ false };
	game.setPaused(true);
// TODO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//Prepare the sound
	Sound soundChop;
	soundChop.setBuffer(soundBufferChop);

	Sound soundDeath;
	soundDeath.setBuffer(soundBufferDeath);

	Sound soundOutOfTime;
	soundOutOfTime.setBuffer(soundBufferOutOfTime);	

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !game.isPaused())
			{
				//Listen for key press again
				acceptInput = true;

				//Hide the axe
				axe.setPosition(vec2{
					HIDDEN_X,
					axe.getPosition().y}
				);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			game.setPaused(false);
			//Reset the time and the score
			game.restart();

			if(!player.isAlive())
				player.reset();
			//Make all branches disappear
			for (unsigned idx = 0; idx < NUM_BRANCHES; ++idx)
				branches[idx].setSideAndHeight(Side::NONE, HIDDEN_Y);

			//Move the player into position
			player.setPosition(vec2{ 580, 720 });

			acceptInput = true;
		}

		if (acceptInput)
		{
			//Handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				game.increaseScore();

				//Play a chop sound
				soundChop.play();

				if (game.getTimeRemaining() <= game.rules.getTimeOnStart() && game.getScore() > 0)
					game.setTimeRemaining(game.getTimeRemaining() + (2.0 / game.getScore()) + game.rules.getTimePerChop());

				axe.setSide(Side::RIGHT);
				player.setSide(Side::RIGHT);

				updateBranches(branches, game.getScore());

				log.setPosition(vec2 { 810, 720 });
				log.setSpeed(vec2{ -5000, log.getSpeed().y });
				
				log.setActive(true);

				acceptInput = false;

				//Update the score text
				std::stringstream ss;
				ss << "Score: " << game.getScore();
				textScore.setString(ss.str());

			}

			//Handle pressing the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				game.increaseScore();

				//Play a chop sound
				soundChop.play();

				if (game.getTimeRemaining() <= game.rules.getTimeOnStart() && game.getScore() > 0)
					game.setTimeRemaining(game.getTimeRemaining() + (2.0 / game.getScore()) + game.rules.getTimePerChop());

				axe.setSide(Side::LEFT);
				player.setSide(Side::LEFT);

				updateBranches(branches, game.getScore());

				log.setPosition(vec2 { 810, 720 });
				log.setSpeed(vec2{ 5000, log.getSpeed().y });

				log.setActive(true);

				acceptInput = false;

				//Update the score text
				std::stringstream ss;
				ss << "Score: " << game.getScore();
				textScore.setString(ss.str());

			}
		}

		if (!game.isPaused())
		{
			Time dt = clock.restart();

			//Subtract from the amount of time remaining
			game.setTimeRemaining(game.getTimeRemaining() - dt.asSeconds());
			//Resize the time bar
			timeBar.setSize(Vector2f(game.getTimeRemaining() * timeBarWidthPerSecond, timeBarHeight));

			if (game.getTimeRemaining() <= 0.f)
			{
				game.setPaused(true);
				textMessage.setString("Out of time!");

				//Reposition the text based on its new size
				FloatRect textRect = textMessage.getLocalBounds();
				textMessage.setOrigin(
					textRect.left + textRect.width / 2.f,
					textRect.top + textRect.height / 2.f
				);

				textMessage.setPosition(WIDTH / 2.f, HEIGHT / 2.f);

				//Play a OutOfTime sound
				soundOutOfTime.play();
			}
			//Move the bee
			bee.fly(dt.asSeconds());

			//Manage the clouds
			for (auto& cloud : clouds)
			{
				cloud.fly(dt.asSeconds());
			}

			// //Update branch sprites
			// updateBranches(branches, game.getScore());

			//Handle a flying log
			log.fly(dt.asSeconds());

			//Has the player been squished by a branch
			if (branches[NUM_BRANCHES - 1].getSide() == player.getSide())
			{
				//Death
				game.setPaused(true);
				acceptInput = false;

				//Draw the gravestone
				player.die();
				axe.setPosition(vec2{ HIDDEN_X, axe.getPosition().y });

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
		
		background.draw();
		for (auto& branch : branches)
		{
			branch.draw();
		}

		tree.draw();
		player.draw();
		axe.draw();
		log.draw();
		bee.draw();

		for (auto& cloud : clouds)
		{
			cloud.draw();
		}
		if (game.isPaused())
			window.draw(textMessage);
		window.draw(textScore);
		window.draw(timeBar);
		window.display();
	}
	return 0;
}

void updateBranches(std::vector<Branch>& branches, int seed)
{
	//Move all branches down one place
	for (unsigned idx = NUM_BRANCHES - 1; idx > 0; --idx)
	{
		float height = idx * 150;
 		branches[idx].setSideAndHeight(branches[idx-1].getSide(), height);
	}
	//Spawn new branch at position 0
	srand((int)time(0) + seed);
	int random = rand() % 2;
	switch (random)
	{
	case 0:
		branches[0].setSideAndHeight(Side::LEFT, 0);
		break;
	case 1:
		branches[0].setSideAndHeight(Side::RIGHT, 0);
		break;
	default:
		branches[0].setSideAndHeight(Side::NONE, 0);
		break;
	}
}
