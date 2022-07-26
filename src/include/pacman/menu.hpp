#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
private:
    sf::RenderWindow & window;
    std::vector<sf::Text> buttons;
    int selectedButton = 0;
    std::vector<sf::Text> labels;
    sf::Font font;
    sf::RectangleShape background;
    float x_location, h_location;
    float x_size, h_size;
    bool visible = false;
public:
    Menu(sf::RenderWindow & w, float size_x = 400, float size_h = 200, sf::Color backColor = sf::Color::White);
    void addLabel(std::string text, unsigned int textSize, float location_x, float location_h, sf::Color color);
    void addButton(std::string text, unsigned int textSize, float location_x, float location_h);
    void selectButton(int n);
    ~Menu();
    void draw(sf::RenderWindow & w);

    void open();
    void close();
};


#endif // MENU_HPP