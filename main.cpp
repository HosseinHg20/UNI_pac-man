#include <SFML/Graphics.hpp>
#include <iostream>
#include <pacman/Animation.hpp>
#include <pacman/pacman.hpp>
#include <pacman/map.hpp>

int main()
{
    int width = 672;
    int height = 672;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    window.setFramerateLimit(60);

    Pacman pacmann(0.01, height / 42);
    Map map(height, width);

    sf::Clock clock;
    while (window.isOpen())
    {
        int acc = map.accident(pacmann.getShape());
        if (acc > 0)
        {
            pacmann.back();
        }
        else if (acc < 0)
        {
            pacmann.scorePlus(-acc);
            window.setTitle(std::to_string(pacmann.getScore()));
        }


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                pacmann.rotate(DIRECTION::LEFT);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                pacmann.rotate(DIRECTION::UP);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                pacmann.rotate(DIRECTION::RIGHT);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                pacmann.rotate(DIRECTION::DOWN);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                pacmann.stop(false);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                pacmann.stop(true);
            }
        }




        pacmann.update();



        window.clear();
        map.draw(window);
        window.draw(pacmann.getShape());
        window.display();
    }

    return 0;
}