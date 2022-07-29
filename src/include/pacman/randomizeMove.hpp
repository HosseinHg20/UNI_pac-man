#ifndef RANDOMIZEMOVE_HPP
#define RANDOMIZEMOVE_HPP

#include <SFML/Graphics.hpp>
#include <pacman/map.hpp>

class RandomizeMove
{
private:
    Map & map;
    sf::RectangleShape & shape;
    sf::Clock clock;
    sf::Time time;

    sf::Vector2f lastMove;
    float stepSize = 3.0;
    bool enable = true;
public:
    RandomizeMove(Map & map, sf::RectangleShape & shape, float time);
    ~RandomizeMove();

    void step();
    void back();
};


#endif // RANDOMIZEMOVE_HPP