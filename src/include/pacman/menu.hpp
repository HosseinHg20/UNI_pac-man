#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
private:
    sf::RenderWindow & window;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> labels;
    sf::RectangleShape background;
    float x_location, h_location;
    float x_size, h_size;
public:
    Menu(sf::RenderWindow & w, float size_x = 400, float size_h = 200, sf::Color backColor = sf::Color::White);
    ~Menu();
    void draw(sf::RenderWindow & w);
};

Menu::Menu(sf::RenderWindow & w, float size_x, float size_h, sf::Color backColor) 
            : window(w), background(sf::Vector2f(size_x, size_h)), x_size(size_x), h_size(size_h)
{
    background.setFillColor(backColor);
    x_location = (w.getSize().x - x_size) / 2;
    h_location = (w.getSize().y - h_size) / 2;
    background.setPosition(x_location, h_location);
}


Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow & w)
{
    w.draw(background);
    for (int i = 0; i < buttons.size(); i++)
        w.draw(buttons[i]);
    for (int i = 0; i < labels.size(); i++)
        w.draw(labels[i]);
}

#endif // MENU_HPP