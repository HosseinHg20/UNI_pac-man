#ifndef MOVE_HPP
#define MOVE_HPP

#include <SFML/Graphics.hpp>

enum class DIRECTION {LEFT, RIGHT, UP, DOWN};

class Move
{
private:
    sf::Shape * shape;
    sf::Clock clock;
    sf::Time time;
    DIRECTION direction = DIRECTION::RIGHT;
    sf::Vector2f lastMove;
    float stepSize = 1.0;
    bool enable = false;
public:
    Move(sf::Shape * sh, float t);

    void step();
    void back();
    void rotate(DIRECTION dir);
    void setenable(bool en);
};

#endif // MOVE_HPP