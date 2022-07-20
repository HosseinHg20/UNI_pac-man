#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
private:
    std::vector<sf::RectangleShape> blocks;
    sf::RectangleShape leftTeleport;
    sf::RectangleShape rightTeleport;
    int h_block;
    int w_block;
public:
    Map(int h, int w);
    void draw(sf::RenderWindow & window);
    int accident(sf::RectangleShape & shape);
};



#endif // MAP_HPP