#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
private:
    sf::RenderWindow & window;
    std::vector<sf::Text> buttons;
    std::vector<sf::Text> labels;
    sf::Font font;
    sf::RectangleShape background;
    float x_location, h_location;
    float x_size, h_size;
    bool visible = false;
    sf::RectangleShape mouse;
public:
    Menu(sf::RenderWindow & w, float size_x = 400, float size_h = 200, sf::Color backColor = sf::Color::White);
    Menu & addLabel(std::string text, unsigned int textSize, float location_x, float location_h, sf::Color color);
    Menu & addButton(std::string text, unsigned int textSize, float location_x, float location_h, sf::Color color);
    void draw(sf::RenderWindow & w);

    int clicked(int x, int h);

    void open();
    void close();
};


#endif // MENU_HPP