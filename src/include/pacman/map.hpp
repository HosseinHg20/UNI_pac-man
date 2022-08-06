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
    sf::RectangleShape door;
    sf::Time _time;
    sf::Clock _clock;
    int h_block;
    int w_block;
    int foodCounter = 0;
    int visibleFoods = 0;
public:
    int specialFoodNumber = -1;
    Map(int h, int w);
    void draw(sf::RenderWindow & window);
    int accident(sf::RectangleShape & shape, bool ghost = false);

    void setRandomFood(fd::Type t);
    void checkSpecoalFood();
    int getFoodCounter();
    int getVisibleFoods();
    void restart();
};



#endif // MAP_HPP