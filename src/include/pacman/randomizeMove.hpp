#ifndef RANDOMIZEMOVE_HPP
#define RANDOMIZEMOVE_HPP

#include <SFML/Graphics.hpp>
#include <pacman/map.hpp>
#include <vector>

enum class _DIRECTION {LEFT, RIGHT, UP, DOWN};

class RandomizeMove
{
private:
    Map & map;
    sf::RectangleShape & shape;
    sf::Clock clock;
    sf::Time time;
    _DIRECTION _direction = _DIRECTION::UP;
    sf::Vector2f lastMove;
    float stepSize = 4.0;
    bool enable = true;
public:
    RandomizeMove(Map & map, sf::RectangleShape & shape, float time);
    ~RandomizeMove();

    void step();
    void back();
    std::vector<_DIRECTION> checkRotation();
    void rotate();
};


#endif // RANDOMIZEMOVE_HPP