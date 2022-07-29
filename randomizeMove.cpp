#include <pacman/randomizeMove.hpp>

RandomizeMove::RandomizeMove(Map & m, sf::RectangleShape & sh, float t) : map(m), shape(sh)
{
    lastMove = sf::Vector2f(0, -stepSize);
    time = sf::seconds(t);
}

RandomizeMove::~RandomizeMove()
{

}

void RandomizeMove::step()
{
    if (clock.getElapsedTime().asSeconds() > time.asSeconds() && enable)
    {
        clock.restart();
        shape.move(lastMove);
    }
}