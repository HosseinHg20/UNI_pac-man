#include <pacman/food.hpp>

fd::Food::Food() : sf::CircleShape(4)
{
    change(Type::Normal);
    txtapple.loadFromFile("./images/apple.png");
}

void fd::Food::change(Type t)
{
    type = t;
    switch (type)
    {
    case Type::Normal:
        setRadius(4);
        setTexture(NULL);
        setFillColor(sf::Color::White);
        break;
    case Type::Strength:
        setRadius(8);
        setTexture(NULL);
        setFillColor(sf::Color::White);
        break;
    case Type::Apple:
        setRadius(12);
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