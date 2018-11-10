#include <sstream>
#include "game.h"
#include "rectangle.h"
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

    std::vector<Drawing> backgroundTrees{Drawing(window, textureBackgroundTree, vec2{250, 800}),
                                         Drawing(window, textureBackgroundTree, vec2{700, 700}),
                                         Drawing(window, textureBackgroundTree, vec2{1700, 750})};
    for (auto& tree : backgroundTrees) tree.setOrigin(200, 800);

    Log log(window, textureLog, vec2{810, 720}, vec2{1000.f, -1500.f});

    std::vector<Branch> branches(NUM_BRANCHES,
                                 Branch(window, textureBranch, vec2{HIDDEN_X, HIDDEN_Y}));
    for (auto& branch : branches) branch.setOrigin(220, 20);

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

    // Prepare texts- score and startGame
    Text textMessage(window, "Press Enter to start", font, 100, sf::Color::White);
    textMessage.center();
    textMessage.setPosition(vec2{WIDTH / 2.f, HEIGHT / 2.f});

    Text textScore(window, "Score: 0", font, 100, sf::Color::White);
    textScore.setPosition(vec2{20.f, 20.f});
    Rectangle backgroundScore(window, vec2{570, 120}, vec2{12, 20}, /*sf::Color*/ {0, 0, 0, 100});

    Text textFps(window, "FPS: ", font, 50, sf::Color::White);
    textFps.setPosition(vec2{300.f, 300.f});

    sf::Clock clock;

    // Prepare time bar
    Rectangle timeBar(window, vec2{TIME_BAR_WIDTH, TIME_BAR_HEIGHT},
                      vec2{WIDTH / 2 - TIME_BAR_WIDTH / 2, 980}, sf::Color::Green);
    float timeBarWidthPerSecond = TIME_BAR_WIDTH / game.getTimeRemaining();

    // Control the player input
    bool acceptInput{false};
    game.setPaused(true);
    sf::Time one_sec;
    while (window.isOpen())  // Game loop
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
            timeBar.resetSize();

            if (not player.isAlive()) player.reset();

            for (unsigned idx = 0; idx < NUM_BRANCHES; ++idx)  // Make all branches disappear
                branches[idx].setSideAndHeight(Side::NONE, HIDDEN_Y);

            player.setPosition(vec2{580, 720});

            acceptInput = true;
        }

        if (acceptInput)
        {
            // Handle pressing the right cursor key
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                game.increaseScore();
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
            timeBar.setSize(vec2{game.getTimeRemaining() * timeBarWidthPerSecond, TIME_BAR_HEIGHT});
            if (game.getTimeRemaining() >= game.rules.getTimeOnStart())
                updateTimeBarColor(timeBar, 1.0);
            else
                updateTimeBarColor(timeBar, game.getTimeRemaining() / game.rules.getTimeOnStart());
            if (game.getTimeRemaining() <= 0.f)
            {
                game.setPaused(true);
                textMessage.setString("Out of time!");
                textMessage.center();
                soundOutOfTime.play();
            }

            bee.fly(dt.asSeconds());  // Move the bee

            for (auto& cloud : clouds) cloud.fly(dt.asSeconds());  // Manage the clouds

            log.fly(dt.asSeconds());  // Handle a flying log

            // Has the player been squished by a branch
            if (branches[NUM_BRANCHES - 1].getSide() == player.getSide())
            {
                // Death
                game.setPaused(true);
                acceptInput = false;

                // Draw the gravestone
                player.die();
                axe.setSide(Side::NONE);

                // Change the text of the message
                textMessage.setString("SQUISHED!");
                textMessage.center();
                textMessage.setPosition(vec2{WIDTH / 2.f, HEIGHT / 2.f});

                soundDeath.play();
            }

        }  // if(not game.isPaused())

        window.clear();

        background.draw();
        for (auto& tree : backgroundTrees) tree.draw();
        for (auto& branch : branches) branch.draw();
        tree.draw();
        player.draw();
        axe.draw();
        log.draw();
        bee.draw();
        for (auto& cloud : clouds) cloud.draw();
        if (game.isPaused()) textMessage.draw();
        backgroundScore.draw();
        textScore.draw();
        timeBar.draw();

        window.display();
    }
    return 0;
}
