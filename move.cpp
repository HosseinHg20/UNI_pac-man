#include <pacman/move.hpp>

Move::Move(sf::Shape * sh, float t)
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
        shape->move(lastMove);
        // shape->move(sf::Vector2f(1, 0));
    }
}
void Move::back()
{
    shape->move(sf::Vector2f(-lastMove.x, -lastMove.y));
}

void Move::rotate(DIRECTION dir)
{
    switch (direction)
    {
    case DIRECTION::UP:
        shape->rotate(90.0);
        break;
    case DIRECTION::LEFT:
        shape->rotate(180.0);
        break;
    case DIRECTION::DOWN:
        shape->rotate(-90.0);
        break;
    }
    direction = DIRECTION::RIGHT;

    switch (dir)
    {
    case DIRECTION::RIGHT:
        lastMove = sf::Vector2f(stepSize, 0);
        break;
    case DIRECTION::LEFT:
        lastMove = sf::Vector2f(-stepSize, 0);
        shape->rotate(180.0);
        break;
    case DIRECTION::UP:
        lastMove = sf::Vector2f(0, -stepSize);
        shape->rotate(-90.0);
        break;
    case DIRECTION::DOWN:
        lastMove = sf::Vector2f(0, stepSize);
        shape->rotate(90.0);
        break;
    }
    direction = dir;
}

void Move::setenable(bool en)
{
    enable = en;
}