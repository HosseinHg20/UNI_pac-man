#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <pacman/menu.hpp>
#include <iostream>

namespace MenuManager
{
    enum class Result {Play, Exit, Resume, NewGame};

    Result startMenu(sf::RenderWindow & window)
    {
        Menu mainMenu(window, 400, 200, sf::Color::White, sf::Color::Green);
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

    Result endMenu(sf::RenderWindow & window, int score)
    {
        Menu menu(window, 400, 200, sf::Color::White, sf::Color::Green);
        menu.addLabel("end!", 30, -1, 10, sf::Color::Black)
            .addLabel("your score : " + std::to_string(score), 20, -1, 50, sf::Color::Black)
            .addLabel("highest score : " + std::to_string(memory::getHighestScore()), 20, -1, 80, sf::Color::Black)
            .addButton("resume", 30, -1, 130, sf::Color::Black)
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
                        }
                    }
                }
                
            }
            window.clear();
            menu.draw(window);
            window.display();
        }
        
    }

    Result lostMenu(sf::RenderWindow & window, int score)
    {
        Menu menu(window, 400, 200, sf::Color::White, sf::Color::Red);
        menu.addLabel("you lost!", 20, -1, 10, sf::Color::Red)
            .addLabel("your score : " + std::to_string(score), 20, -1, 40, sf::Color::Black)
            .addLabel("highest score : " + std::to_string(memory::getHighestScore()), 20, -1, 70, sf::Color::Black)
            .addButton("play again", 30, 70, 130, sf::Color::Black)
            .addButton("exit", 30, 270, 130, sf::Color::Black)
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
                            return Result::NewGame;
                            break;
                        case 1:
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