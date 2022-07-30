#include <pacman/randomizeMove.hpp>
#include <iostream> // test

RandomizeMove::RandomizeMove(Map & m, sf::RectangleShape & sh, float t) : map(m), shape(sh)
{
    lastMove = sf::Vector2f(0, -stepSize);
    time = sf::seconds(t);
}

RandomizeMove::~RandomizeMove()
{

}

_DIRECTION RandomizeMove::step()
{
    if (clock.getElapsedTime().asSeconds() > time.asSeconds() && enable)
    {
        clock.restart();
        shape.move(lastMove);
        if (map.accident(shape, true))
            back();
        return rotate();
    }
}

void RandomizeMove::back()
{
    shape.move(-lastMove);
}


std::vector<_DIRECTION> RandomizeMove::checkRotation()
{
    std::vector<_DIRECTION> result;

    shape.move(sf::Vector2f(4, 0));
    if (!map.accident(shape, true) && _direction != _DIRECTION::LEFT)
        result.push_back(_DIRECTION::RIGHT);
    // shape.move(sf::Vector2f(-10, 0));

    shape.move(sf::Vector2f(-8, 0));

    // shape.move(sf::Vector2f(-10, 0));
    if (!map.accident(shape, true) && _direction != _DIRECTION::RIGHT)
        result.push_back(_DIRECTION::LEFT);
    // shape.move(sf::Vector2f(10, 0));
    
    shape.move(sf::Vector2f(4, 4));

    // shape.move(sf::Vector2f(0, 6));
    if (!map.accident(shape, true) && _direction != _DIRECTION::UP)
        result.push_back(_DIRECTION::DOWN);
    // shape.move(sf::Vector2f(0, -6));

    shape.move(sf::Vector2f(0, -8));

    // shape.move(sf::Vector2f(0, -6));
    if (!map.accident(shape, true) && _direction != _DIRECTION::DOWN)
        result.push_back(_DIRECTION::UP);
    shape.move(sf::Vector2f(0, 4));
    
    return result;
}

_DIRECTION RandomizeMove::rotate()
{
    std::vector<_DIRECTION> canRotate = checkRotation();
    switch (_direction)
    {
    case _DIRECTION::RIGHT:
        std::cout << "\nDirection : right\n";
        break;
    case _DIRECTION::LEFT:
        std::cout << "\nDirection : left\n";
        break;
    case _DIRECTION::UP:
        std::cout << "\nDirection : up\n";
        break;
    case _DIRECTION::DOWN:
        std::cout << "\nDirection : down\n";
        break;
    }
    for (int i = 0; i < canRotate.size(); i++) // test
    {
        switch (canRotate[i])
        {
        case _DIRECTION::RIGHT:
            std::cout << " - right - ";
            break;
        case _DIRECTION::LEFT:
            std::cout << " - left - ";
            break;
        case _DIRECTION::UP:
            std::cout << " - up - ";
            break;
        case _DIRECTION::DOWN:
            std::cout << " - down - ";
            break;
        }
    }
    // getchar();// test
    


    if (canRotate.size() == 0)
    {
        shape.move(lastMove);
    }
    else if (canRotate.size() == 1 && canRotate[0] == _direction)
        return _direction;
    else
    {
        int random_Direction = rand() % canRotate.size();
        switch (canRotate[random_Direction])
        {
        case _DIRECTION::RIGHT:
            lastMove = sf::Vector2f(stepSize, 0);
            _direction = _DIRECTION::RIGHT;
            return _DIRECTION::RIGHT;
            break;
        case _DIRECTION::LEFT:
            lastMove = sf::Vector2f(-stepSize, 0);
            _direction = _DIRECTION::LEFT;
            return _DIRECTION::LEFT;
            break;
        case _DIRECTION::UP:
            lastMove = sf::Vector2f(0, -stepSize);
            _direction = _DIRECTION::UP;
            return _DIRECTION::UP;
            break;
        case _DIRECTION::DOWN:
            lastMove = sf::Vector2f(0, stepSize);
            _direction = _DIRECTION::DOWN;
            return _DIRECTION::DOWN;
            break;
        }
    }
}