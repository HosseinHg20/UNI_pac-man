#include <SFML/Graphics.hpp>
#include <iostream>
#include <pacman/Animation.hpp>
#include <pacman/pacman.hpp>
#include <pacman/map.hpp>
#include <pacman/score.hpp>
#include <pacman/menu.hpp>
#include <pacman/menuManager.hpp>
// #include <pacman/ghosts.hpp>
#include <pacman/ghost.hpp>
#include <pacman/ghostManager.hpp>


int main()
{
    // set time for random numbers
    srand(time(0));

    // a window for all of game
    int width = 672;
    int height = 672;
    sf::RenderWindow window(sf::VideoMode(width, height + 56), "SFML works!");
    window.setFramerateLimit(60);

    // start menu was called
    MenuManager::Result result = MenuManager::startMenu(window);
    switch (result)
    {
    case MenuManager::Result::Exit:
        return 0;
        break;
    }

    // this shapes can show hp to player bottom the window
    sf::Texture hp;
    hp.loadFromFile("./images/pacman2.png");
    sf::CircleShape hp1(16);
    hp1.setTexture(&hp);
    hp1.setPosition(width - 128, height + 10);
    sf::CircleShape hp2(16);
    hp2.setTexture(&hp);
    hp2.setPosition(width - 88, height + 10);
    sf::CircleShape hp3(16);
    hp3.setTexture(&hp);
    hp3.setPosition(width - 48, height + 10);

    // this text can show score to player bottom the window
    sf::Font font;
    if (!font.loadFromFile("./fonts/arial.ttf"))
        return 0;
    sf::Text txtscore;
    txtscore.setString("score : 0");
    txtscore.setFont(font);
    txtscore.setPosition(10, height + 10);

    // making a map
    Map map(height, width);

    // making a pacman
    Pacman pacmann(map, 0.01, height / 42);

    // making a ghostManager and adding four ghost to it
    GhostManager ghosts(map);
    ghosts.addGhost(); 
    ghosts.addGhost(); 
    ghosts.addGhost(); 
    ghosts.addGhost(); 

    // main loop
    while (window.isOpen())
    {    
        sf::Clock clock;
        pacmann.stop(false);
        [&]{
            while (window.isOpen())
            {
                // check the completion of the level
                if (map.getVisibleFoods() <= 0)
                {
                    pacmann.restart(true, false, false);
                    if (pacmann.getScore() > memory::getHighestScore())
                        memory::saveHighestScore(pacmann.getScore());
                    result = MenuManager::endMenu(window, pacmann.getScore());
                    ghosts.restart();
                    return;
                }

                // check the collision
                int acc = map.accident(pacmann.getShape());
                // collision (pacman vs wall)
                if (acc > 0)
                {
                    pacmann.back();
                }
                // collision (pacman vs foods)
                else if (acc < 0)
                {
                    pacmann.scorePlus(-acc);
                    if (acc == -50)
                        ghosts.setScare();
                }
                // check the collision (pacman vs ghost)
                acc = ghosts.accident(pacmann.getShape());
                // collision (normal ghost vs pacman)
                if (acc > 0)
                {
                    pacmann.backToHome();
                    ghosts.restart();
                    if (pacmann.subHP() < 0)
                    {
                        if (pacmann.getScore() > memory::getHighestScore())
                            memory::saveHighestScore(pacmann.getScore());
                        result = MenuManager::lostMenu(window, pacmann.getScore());
                        switch (result)
                        {
                        case MenuManager::Result::NewGame:
                            pacmann.restart(true, true, true);
                            ghosts.restart();
                            return;
                            break;
                        case MenuManager::Result::Exit:
                            window.close();
                            return;
                            break;
                        }
                    }
                }
                // collision (scared ghost vs pacman)
                else if (acc < 0)
                {
                    ghosts.backToHome(-acc);
                    pacmann.scorePlus(200);

                }

                // check input events
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -0.9)
                    {
                        pacmann.rotate(DIRECTION::LEFT);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -0.9)
                    {
                        pacmann.rotate(DIRECTION::UP);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 0.9)
                    {
                        pacmann.rotate(DIRECTION::RIGHT);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 0.9)
                    {
                        pacmann.rotate(DIRECTION::DOWN);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        result = MenuManager::stopMenu(window);
                        switch (result)
                        {
                        case MenuManager::Result::Exit:
                            window.close();
                            break;
                        case MenuManager::Result::Resume:
                            continue;
                            break;
                        case MenuManager::Result::NewGame:
                            pacmann.restart(true, true, true);
                            ghosts.restart();
                            return;
                            break;
                        }
                    }
                }

                
                pacmann.update();
                ghosts.update();

                txtscore.setString("score : " + std::to_string(pacmann.getScore()));

                if (map.getFoodCounter() == 70 || map.getFoodCounter() == 170)
                    map.setRandomFood(fd::Type::Apple);
                map.checkSpecoalFood();


                window.clear();
                ghosts.draw(window);
                map.draw(window);
                window.draw(pacmann.getShape());
                if (pacmann.getHP() > 0)
                    window.draw(hp3);
                if (pacmann.getHP() > 1)
                    window.draw(hp2);
                if (pacmann.getHP() > 2)
                    window.draw(hp1);
                window.draw(txtscore);
                window.display();
            }
        }();
    }
    return 0;
}