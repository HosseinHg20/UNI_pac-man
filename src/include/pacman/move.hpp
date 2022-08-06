#ifndef MOVE_HPP
#define MOVE_HPP

#include <SFML/Graphics.hpp>
#include <pacman/map.hpp>

enum class DIRECTION {LEFT, RIGHT, UP, DOWN};

class Move
{
private:
    Map & map;
    sf::RectangleShape & shape;
    sf::Clock clock;
    sf::Time time;
    DIRECTION direction = DIRECTION::RIGHT;
    DIRECTION changeDirectionTo = DIRECTION::RIGHT;
    sf::Vector2f lastMove;
    float stepSize = 3.0;
    bool enable = false;
    void rotate();
public:
    Move(Map & m, sf::RectangleShape & sh, float t);

    void step();
    void back();
    void setRotate(DIRECTION dir);
    void setenable(bool en);
};

#endif // MOVE_HPP