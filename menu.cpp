#include <pacman/menu.hpp>

Menu::Menu(sf::RenderWindow & w, float size_x, float size_h, sf::Color backColor) 
            : window(w), background(sf::Vector2f(size_x, size_h)), x_size(size_x), h_size(size_h)
{
    font.loadFromFile("./fonts/arial.ttf");

    background.setFillColor(backColor);
    x_location = (w.getSize().x - x_size) / 2;
    h_location = (w.getSize().y - h_size) / 2;
    background.setPosition(x_location, h_location);
}

void Menu::addLabel(std::string text, unsigned int textSize, float location_x, float location_h, sf::Color color)
{
    sf::Text t(text, font);
    t.setCharacterSize(textSize);
    t.setPosition(location_x + x_location, location_h + h_location);
    t.setFillColor(color);

    labels.push_back(t);
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow & w)
{
    if (visible)
    {
        w.draw(background);
        for (int i = 0; i < buttons.size(); i++)
            w.draw(buttons[i]);
        for (int i = 0; i < labels.size(); i++)
            w.draw(labels[i]);
    }
}


void Menu::open()
{
    visible = true;
}
void Menu::close()
{
    visible = false;
}