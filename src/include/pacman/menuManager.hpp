#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <pacman/menu.hpp>

namespace MenuManager
{
    enum class Result {Play, Exit, Again};

    Result startMenu(sf::RenderWindow & window)
    {
        Menu mainMenu(window);
        mainMenu.addLabel("stop!", 30, -1, 10, sf::Color::Red);

        mainMenu.addButton("Play", 20, -1, 80);
        mainMenu.addButton("restart game", 20, -1, 120);
        mainMenu.addButton("exit", 20, -1, 160);
        mainMenu.open();

        sf::RectangleShape mouse(sf::Vector2f(10, 10));
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                    
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    return Result::Exit;
                }
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
                        case 2:
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
    
} // namespace MenuManager


#endif // MENUMANAGER_HPP