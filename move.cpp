#include <pacman/move.hpp>

Move::Move(Map & m, sf::RectangleShape & sh, float t) : map(m) , shape(sh)
{
    lastMove = sf::Vector2f(stepSize, 0);
    shape = sh;
    time = sf::seconds(t);
}


void Move::step()
{
    if (clock.getElapsedTime().asSeconds() > time.asSeconds() && enable)
    {
        clock.restart();
        rotate();
        shape.move(lastMove);
    }
}
void Move::back()
{
    shape.move(sf::Vector2f(-lastMove.x, -lastMove.y));
}

void Move::setRotate(DIRECTION dir)
{
    changeDirectionTo = dir;
}

void Move::rotate()
{
    if (direction == changeDirectionTo)
        return;
    
    int acc;
    switch (changeDirectionTo)
    {
    case DIRECTION::UP:
        shape.move(0, -stepSize * 10);
        acc = map.accident(shape);
        shape.move(0, stepSize * 10);
        break;
    case DIRECTION::DOWN:
        shape.move(0, stepSize * 10);
        acc = map.accident(shape);
        shape.move(0, -stepSize * 10);
        break;
    case DIRECTION::RIGHT:
        shape.move(stepSize * 10, 0);
        acc = map.accident(shape);
        shape.move(-stepSize * 10, 0);
        break;
    case DIRECTION::LEFT:
        shape.move(-stepSize * 10, 0);
        acc = map.accident(shape);
        shape.move(stepSize * 10, 0);
        break;
    }
    if (acc > 0)
        return;


    switch (direction)
    {
    case DIRECTION::UP:
        shape.rotate(90.0);
        break;
    case DIRECTION::LEFT:
        shape.rotate(180.0);
        break;
    case DIRECTION::DOWN:
        shape.rotate(-90.0);
        break;
    }
    direction = DIRECTION::RIGHT;

    switch (changeDirectionTo)
    {
    case DIRECTION::RIGHT:
        lastMove = sf::Vector2f(stepSize, 0);
        break;
    case DIRECTION::LEFT:
        lastMove = sf::Vector2f(-stepSize, 0);
        shape.rotate(180.0);
        break;
    case DIRECTION::UP:
        lastMove = sf::Vector2f(0, -stepSize);
        shape.rotate(-90.0);
        break;
    case DIRECTION::DOWN:
        lastMove = sf::Vector2f(0, stepSize);
        shape.rotate(90.0);
        break;
    }
    direction = changeDirectionTo;
}

void Move::setenable(bool en)
{
    enable = en;
}

void Move::changeDirection(DIRECTION dir)
{
    changeDirectionTo = dir;
}