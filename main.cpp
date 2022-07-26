#include <SFML/Graphics.hpp>
#include <iostream>
#include <pacman/Animation.hpp>
#include <pacman/pacman.hpp>
#include <pacman/map.hpp>
#include <pacman/score.hpp>
#include <pacman/menu.hpp>

int main()
{
    int highestScore = memory::getHighestScore();

    int width = 672;
    int height = 672;
    sf::RenderWindow window(sf::VideoMode(width, height + 56), "SFML works!");
    window.setFramerateLimit(60);

    Menu mainMenu(window);

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

    sf::Clock clock;
    while (window.isOpen())
    {
        if (map.getVisibleFoods() <= 0)
        {
            pacmann.restart(true, false, false);
            if (pacmann.getScore() > highestScore)
            {
                highestScore = pacmann.getScore();
                memory::saveHighestScore(highestScore);
            }
            
        }

        int acc = map.accident(pacmann.getShape());
        if (acc > 0)
        {
            pacmann.back();
        }
        else if (acc < 0)
        {
            pacmann.scorePlus(-acc);
            if (acc == -100)
                pacmann.subHP();
            // window.setTitle(std::to_string(acc));
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                pacmann.stop(false);
                mainMenu.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                pacmann.stop(true);
                mainMenu.open();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {
                pacmann.restart(true, false, false);
            }
        }

        pacmann.update();

        txtscore.setString("score : " + std::to_string(pacmann.getScore()));

        window.setTitle(std::to_string(map.getFoodCounter()) + ", " + std::to_string(map._clock.getElapsedTime().asSeconds())
                        + ", " + std::to_string(highestScore) + ", " + std::to_string(map.getVisibleFoods()) + ", " + std::to_string(map.specialFoodNumber));
        if (map.getFoodCounter() == 70 || map.getFoodCounter() == 170)
            map.setRandomFood(fd::Type::Apple);
        map.checkSpecoalFood();


        window.clear();
        map.draw(window);
        window.draw(pacmann.getShape());
        if (pacmann.getHP() > 0)
            window.draw(hp3);
        if (pacmann.getHP() > 1)
            window.draw(hp2);
        if (pacmann.getHP() > 2)
            window.draw(hp1);
        window.draw(txtscore);
        mainMenu.draw(window);
        window.display();
    }

    return 0;
}