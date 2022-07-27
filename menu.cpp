#include <pacman/menu.hpp>

Menu::Menu(sf::RenderWindow & w, float size_x, float size_h, sf::Color backColor) 
            : window(w), background(sf::Vector2f(size_x, size_h)), x_size(size_x), h_size(size_h), mouse(sf::Vector2f(20, 20))
{
    font.loadFromFile("./fonts/arial.ttf");
    mouse.setOrigin(10, 10);

    background.setFillColor(backColor);
    background.setOutlineColor(sf::Color::Red);
    background.setOutlineThickness(5);
    x_location = (w.getSize().x - x_size) / 2;
    h_location = (w.getSize().y - h_size) / 2;
    background.setPosition(x_location, h_location);
}


/**
 * @brief 
 * 
 * @param location_x          use (-1) for centralized label in horizontal
 * @param location_h          use (-1) for centralized label in vertical
 */
Menu & Menu::addLabel(std::string text, unsigned int textSize, float location_x, float location_h, sf::Color color) 
{
    sf::Text t(text, font);
    t.setCharacterSize(textSize);
    if (location_x == -1)
        location_x = (background.getSize().x - (t.getCharacterSize() * text.size() * 17 / 40)) / 2;
    if (location_h == -1)
        location_h = (background.getSize().y - t.getCharacterSize()) / 2;
    t.setPosition(location_x + x_location, location_h + h_location);
    
    t.setFillColor(color);

    labels.push_back(t);
    return *this;
}

/**
 * @brief 
 * 
 * @param location_x          use (-1) for centralized label in horizontal
 * @param location_h          use (-1) for centralized label in vertical
 */
Menu & Menu::addButton(std::string text, unsigned int textSize, float location_x, float location_h, sf::Color color)
{
    sf::Text t(text, font);
    t.setCharacterSize(textSize);
    if (location_x == -1)
        location_x = (background.getSize().x - (t.getCharacterSize() * text.size() * 17 / 40)) / 2;
    if (location_h == -1)
        location_h = (background.getSize().y - t.getCharacterSize()) / 2;
    t.setPosition(location_x + x_location, location_h + h_location);
    
    t.setFillColor(color);
    buttons.push_back(t);

    return *this;
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


int Menu::clicked(int x, int h)
{
    mouse.setPosition(x, h);
    for (int i = 0; i < buttons.size(); i++)
        if (mouse.getGlobalBounds().intersects(buttons[i].getGlobalBounds()))
            return i;
    return -1;
}


void Menu::open()
{
    visible = true;
}
void Menu::close()
{
    visible = false;
}