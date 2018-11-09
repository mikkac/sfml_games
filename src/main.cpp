// TODO refactor texts and rectangles

#include <sstream>
#include "game.h"
#include "text.h"

using namespace timber;

int main()
{
    // Create game and rules
    Rules rules(6.0f, 0.15, 1.0f);
    Game game(rules);

    // Create window
    sf::VideoMode vm(WIDTH, HEIGHT);
    sf::RenderWindow window(vm, "Timber", sf::Style::Fullscreen);

    // Create objects
    Drawing background(window, textureBackground);
    Drawing tree(window, textureTree, vec2{810, 0});

    Log log(window, textureLog, vec2{810, 720}, vec2{1000.f, -1500.f});

    std::vector<Branch> branches(NUM_BRANCHES,
                                 Branch(window, textureBranch, vec2{HIDDEN_X, HIDDEN_Y}));
    for (auto& branch : branches)
    {
        branch.setOrigin(220, 20);
    }

    std::vector<Cloud> clouds(NUM_CLOUDS,
                              Cloud(window, textureCloud, vec2{HIDDEN_X, float(rand_num(300))}));

    Bee bee(window, textureBee);

    Player player(window, texturePlayer, textureGravestone, vec2{580, 720});
    player.setSide(Side::LEFT);

    Axe axe(window, textureAxe, vec2{700, 830});

    // Prepare the sound
    sf::Sound soundChop;
    soundChop.setBuffer(soundBufferChop);

    sf::Sound soundDeath;
    soundDeath.setBuffer(soundBufferDeath);

    sf::Sound soundOutOfTime;
    soundOutOfTime.setBuffer(soundBufferOutOfTime);

    // TODO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Texts- score and startGame
    Text textMessage(window, "Press Enter to start", font, 100, sf::Color::White);
    textMessage.center();
    textMessage.setPosition(vec2{WIDTH / 2.f, HEIGHT / 2.f});

    Text textScore(window, "Score: 0", font, 100, sf::Color::White);
    textScore.setPosition(vec2{20.f, 20.f});
    // // Set the font to our texts
    // textMessage.setFont(font);
    // textScore.setFont(font);

    // // Set rest of text properties
    // textMessage.setString("Press Enter to start");
    // textScore.setString("Score: 0");
    // textMessage.setCharacterSize(75);
    // textScore.setCharacterSize(100);
    // textMessage.setFillColor(sf::Color::White);
    // textScore.setFillColor(sf::Color::White);

    // // Position of text
    // sf::FloatRect textRect = textMessage.getLocalBounds();
    // textMessage.setOrigin(textRect.left + textRect.width / 2.f,
    //                       textRect.top + textRect.height / 2.f);

    sf::Clock clock;

    // Time bar
    sf::RectangleShape timeBar;
    float timeBarStartWidth{400.f};
    float timeBarHeight{80.f};
    timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setPosition(WIDTH / 2 - timeBarStartWidth / 2, 980);

    float timeBarWidthPerSecond = timeBarStartWidth / game.getTimeRemaining();

    // TODO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    // Control the player input
    bool acceptInput{false};
    game.setPaused(true);
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased && not game.isPaused())
            {
                acceptInput = true;
                axe.setPosition(vec2{HIDDEN_X, axe.getPosition().y});  // Hide the axe
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            game.setPaused(false);
            // Reset the time and the score
            game.restart();

            if (not player.isAlive()) player.reset();
            // Make all branches disappear
            for (unsigned idx = 0; idx < NUM_BRANCHES; ++idx)
                branches[idx].setSideAndHeight(Side::NONE, HIDDEN_Y);

            // Move the player into position
            player.setPosition(vec2{580, 720});

            acceptInput = true;
        }

        if (acceptInput)
        {
            // Handle pressing the right cursor key
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                game.increaseScore();

                // Play a chop sound
                soundChop.play();

                if (game.getTimeRemaining() <= game.rules.getTimeOnStart() && game.getScore() > 0)
                    game.setTimeRemaining(game.getTimeRemaining() + (2.0 / game.getScore()) +
                                          game.rules.getTimePerChop());

                axe.setSide(Side::RIGHT);
                player.setSide(Side::RIGHT);

                updateBranches(branches);

                log.setPosition(vec2{810, 720});
                log.setSpeed(vec2{-5000, log.getSpeed().y});

                log.setActive(true);

                acceptInput = false;

                // Update the score text
                std::stringstream ss;
                ss << "Score: " << game.getScore();
                textScore.setString(ss.str().c_str());
            }

            // Handle pressing the left cursor key
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                game.increaseScore();

                // Play a chop sound
                soundChop.play();

                if (game.getTimeRemaining() <= game.rules.getTimeOnStart() && game.getScore() > 0)
                    game.setTimeRemaining(game.getTimeRemaining() + (2.0 / game.getScore()) +
                                          game.rules.getTimePerChop());

                axe.setSide(Side::LEFT);
                player.setSide(Side::LEFT);

                updateBranches(branches);

                log.setPosition(vec2{810, 720});
                log.setSpeed(vec2{5000, log.getSpeed().y});

                log.setActive(true);

                acceptInput = false;

                // Update the score text
                std::stringstream ss;
                ss << "Score: " << game.getScore();
                textScore.setString(ss.str().c_str());
            }
        }

        if (not game.isPaused())
        {
            sf::Time dt = clock.restart();

            // Subtract from the amount of time remaining
            game.setTimeRemaining(game.getTimeRemaining() - dt.asSeconds());
            // Resize the time bar
            timeBar.setSize(
                sf::Vector2f(game.getTimeRemaining() * timeBarWidthPerSecond, timeBarHeight));

            if (game.getTimeRemaining() <= 0.f)
            {
                game.setPaused(true);
                textMessage.setString("Out of time!");
                textMessage.center();
                soundOutOfTime.play();
            }
            // Move the bee
            bee.fly(dt.asSeconds());

            // Manage the clouds
            for (auto& cloud : clouds)
            {
                cloud.fly(dt.asSeconds());
            }

            // //Update branch sprites
            // updateBranches(branches, game.getScore());

            // Handle a flying log
            log.fly(dt.asSeconds());

            // Has the player been squished by a branch
            if (branches[NUM_BRANCHES - 1].getSide() == player.getSide())
            {
                // Death
                game.setPaused(true);
                acceptInput = false;

                // Draw the gravestone
                player.die();
                axe.setPosition(vec2{HIDDEN_X, axe.getPosition().y});

                // Change the text of the message
                textMessage.setString("SQUISHED!");
                textMessage.center();
                textMessage.setPosition(vec2{WIDTH / 2.f, HEIGHT / 2.f});

                // Play a death sound
                soundDeath.play();
            }

        }  // if(not game.isPaused())

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
        for (auto& cloud : clouds) cloud.draw();
        // if (game.isPaused()) window.draw(textMessage);
        // window.draw(textScore);
        if (game.isPaused()) textMessage.draw();
        textScore.draw();
        window.draw(timeBar);
        window.display();
    }
    return 0;
}
