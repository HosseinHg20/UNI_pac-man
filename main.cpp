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
    srand(time(0));
    
    int width = 672;
    int height = 672;
    sf::RenderWindow window(sf::VideoMode(width, height + 56), "SFML works!");
    window.setFramerateLimit(60);
    
    MenuManager::Result result = MenuManager::startMenu(window);
    switch (result)
    {
    case MenuManager::Result::Exit:
        return 0;
        break;
    }

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

    sf::Font font;
    if (!font.loadFromFile("./fonts/arial.ttf"))
        return 0;
    sf::Text txtscore;
    txtscore.setString("score : 0");
    txtscore.setFont(font);
    txtscore.setPosition(10, height + 10);

    Map map(height, width);
    Pacman pacmann(map, 0.01, height / 42);

    // GhostsManager ghosts(map);
    // Ghost ghost(map, 0.01);
    GhostManager ghosts;
    ghosts.addGhost(map); 

    while (window.isOpen())
    {    
        sf::Clock clock;
        pacmann.stop(false);
        [&]{
            while (window.isOpen())
            {
                if (map.getVisibleFoods() <= 0)
                {
                    pacmann.restart(true, false, false);
                    if (pacmann.getScore() > memory::getHighestScore())
                        memory::saveHighestScore(pacmann.getScore());
                    result = MenuManager::endMenu(window, pacmann.getScore());
                    return;
                    
                }

                int acc = map.accident(pacmann.getShape());
                if (acc > 0)
                {
                    pacmann.back();
                }
                else if (acc < 0)
                {
                    pacmann.scorePlus(-acc);
                    // window.setTitle(std::to_string(acc));
                }
                acc = ghosts.accident(pacmann.getShape());
                if (acc)
                {
                    pacmann.backToHome();
                    if (pacmann.subHP() < 0)
                    {
                        if (pacmann.getScore() > memory::getHighestScore())
                            memory::saveHighestScore(pacmann.getScore());
                        result = MenuManager::lostMenu(window, pacmann.getScore());
                        switch (result)
                        {
                        case MenuManager::Result::NewGame:
                            pacmann.restart(true, true, true);
                            return;
                            break;
                        case MenuManager::Result::Exit:
                            window.close();
                            return;
                            break;
                        }
                    }
                }

                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        pacmann.rotate(DIRECTION::LEFT);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    {
                        pacmann.rotate(DIRECTION::UP);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        pacmann.rotate(DIRECTION::RIGHT);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    {
                        pacmann.rotate(DIRECTION::DOWN);
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                    {
                        ghosts.addGhost(map);
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
                            return;
                            break;
                        }
                    }
                }

                pacmann.update();
                // ghost.update();
                ghosts.update();

                txtscore.setString("score : " + std::to_string(pacmann.getScore()));

                window.setTitle(std::to_string(map.getFoodCounter()) + ", " + std::to_string(map._clock.getElapsedTime().asSeconds())
                                + ", " +/* std::to_string(highestScore) + ", " +*/ std::to_string(map.getVisibleFoods()) + ", " + std::to_string(map.specialFoodNumber));
                if (map.getFoodCounter() == 70 || map.getFoodCounter() == 170)
                    map.setRandomFood(fd::Type::Apple);
                map.checkSpecoalFood();


                window.clear();
                // ghosts.draw(window);
                // window.draw(ghost.getShape());
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
                // mainMenu.draw(window);
                window.display();
            }
        }();
    }
    return 0;
}