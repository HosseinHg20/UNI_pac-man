#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <pacman/menu.hpp>

namespace MenuManager
{
    enum class Result {Play, Exit, Resume, NewGame};

    Result startMenu(sf::RenderWindow & window)
    {
        Menu mainMenu(window);
        mainMenu.addLabel("Welcome back Man :)", 30, -1, 20, sf::Color::Green)
                .addLabel("best record : " + std::to_string(memory::getHighestScore()), 15, -1, 60, sf::Color::Black)
                .addButton("play", 20, -1, 110, sf::Color::Black)
                .addButton("exit", 20, -1, 160, sf::Color::Black)
                .open();

        sf::RectangleShape mouse(sf::Vector2f(10, 10));
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        int result = mainMenu.clicked(event.mouseButton.x, event.mouseButton.y);
                        switch (result)
                        {
                        case -1:
                            continue;
                            break;
                        case 0:
                            return Result::Play;
                            break;
                        case 1:
                            return Result::Exit;
                            break;
                        }
                    }
                }
                
            }
            window.clear();
            mainMenu.draw(window);
            window.display();
        }
    }

    Result stopMenu(sf::RenderWindow & window)
    {
        Menu menu(window);
        menu.addLabel("Stop!", 30, -1, 20, sf::Color::Red)
            .addButton("resume", 20, -1, 80, sf::Color::Black)
            .addButton("New Game", 20, -1, 120, sf::Color::Black)
            .addButton("exit", 20, -1, 160, sf::Color::Black)
            .open();
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        int result = menu.clicked(event.mouseButton.x, event.mouseButton.y);
                        switch (result)
                        {
                        case -1:
                            continue;
                            break;
                        case 0:
                            return Result::Resume;
                            break;
                        case 1:
                            return Result::NewGame;
                            break;
                        case 2:
                            return Result::Exit;
                            break;
                        }
                    }
                }
                
            }
            window.clear();
            menu.draw(window);
            window.display();
        }
    }
    
} // namespace MenuManager


#endif // MENUMANAGER_HPP