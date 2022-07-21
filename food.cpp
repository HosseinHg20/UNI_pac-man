#include <pacman/food.hpp>

fd::Food::Food() : sf::CircleShape(4)
{
    change(Type::Normal);
    txtapple.loadFromFile("./images/apple.png");
}

void fd::Food::change(Type t)
{
    type = t;
    switch (t)
    {
    case Type::Normal:
        setOrigin(2, 2);
        setRadius(4);
        setFillColor(sf::Color::White);
        break;
    case Type::Strength:
        setOrigin(4, 4);
        setRadius(8);
        move(-2, -2);
        setFillColor(sf::Color::White);
        break;
    case Type::Apple:
        setOrigin(6, 6);
        setRadius(12);
        move(-4, -4);
        setTexture(&txtapple);
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