#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <pacman/food.hpp>

class Map
{
private:
    std::vector<sf::RectangleShape> blocks;
    std::vector<fd::Food> foods;
    sf::RectangleShape leftTeleport;
    sf::RectangleShape rightTeleport;
    int h_block;
    int w_block;
public:
    Map(int h, int w);
    void draw(sf::RenderWindow & window);
    int accident(sf::RectangleShape & shape);

    void setRandomFood(fd::Type t);
};



#endif // MAP_HPP