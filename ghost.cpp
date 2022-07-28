#include <pacman/ghost.hpp>

Ghost::Ghost(Map & m, float s) : ghost(sf::Vector2f(28, 28))
                                , map(m)
                                , animation_right(&ghost, "./images/ghosts _r_1.png", 0.1)
                                , animation_left(&ghost, "./images/ghosts _l_1.png", 0.1)
                                , move(map, ghost, s)
{
    ghost.setOrigin(14, 14);
    ghost.setPosition(336, 624 - 320);
    animation_right.addTextur("./images/ghosts _r_2.png");
    animation_left.addTextur("./images/ghosts _l_2.png");
    animation_right.setenable(true);
}

Ghost::~Ghost()
{
}

void Ghost::changeAnimationStatus(AnimationStatus a)
{
    if (a == animationStatus)
        return;
    
    switch (animationStatus)
    {
    case AnimationStatus::Right:
        animation_right.setenable(false);
        break;
    case AnimationStatus::Left:
        animation_left.setenable(false);
        break;
    }

    switch (a)
    {
    case AnimationStatus::Right:
        animation_right.setenable(true);
        break;
    case AnimationStatus::Left:
        animation_left.setenable(true);
        break;
    }

    animationStatus = a;
}

void Ghost::update()
{
    switch (animationStatus)
    {
    case AnimationStatus::Right:
        animation_right.update();
        break;
    case AnimationStatus::Left:
        animation_left.update();
        break;
    }
}


sf::RectangleShape Ghost::getShape()
{
    return ghost;
}