#include <pacman/food.hpp>

fd::Food::Food() : sf::CircleShape(4)
{
    change(Type::Normal);
}

void fd::Food::change(Type t)
{
    type = t;
    switch (t)
    {
    case Type::Normal:
        setRadius(4);
        setOrigin(2, 2);
        setFillColor(sf::Color::White);
        break;
    case Type::Strength:
        setRadius(8);
        setOrigin(4, 4);
        setFillColor(sf::Color::White);
        break;
    }
}

fd::Type fd::Food::getType()
{
    return type;
}

void fd::Food::setVisibility(bool v)
{
    visible = v;
    if (visible)
        change(Type::Normal);
    else
        setFillColor(sf::Color::Black);
}

bool fd::Food::getVisibility()
{
    return visible;
}