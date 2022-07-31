#include <pacman/ghost.hpp>

Ghost::Ghost(Map & m, float s) : ghost(sf::Vector2f(29, 29))
                                , map(m)
                                , move(map, ghost, s)
{
    ghost.setOrigin(14, 14);
    ghost.setPosition(336, 624 - 320);
    animation = new RightAnimation(ghost);
}

Ghost::~Ghost()
{
    delete animation;
}

void Ghost::changeAnimationStatus(AnimationStatus a)
{
    if (a == AnimationStatus::Scared)
        clock.restart();
    if (a == animationStatus)
        return;

    delete animation;

    switch (a)
    {
    case AnimationStatus::Left:
        animation = new LeftAnimation(ghost);
        break;
    case AnimationStatus::Right:
        animation = new RightAnimation(ghost);
        break;
    case AnimationStatus::Scared:
        animation = new ScaredAnimation(ghost);
        break;
    case AnimationStatus::DiedRight:
        animation = new RightDiedAnimation(ghost);
        break;
    case AnimationStatus::DiedLeft:
        animation = new LeftDiedAnimation(ghost);
        break;
    }

    animationStatus = a;
}

void Ghost::update()
{
    animation->update();

    if (animationStatus == AnimationStatus::Scared)
        if (clock.getElapsedTime().asSeconds() > ScaredTime.asSeconds())
            changeAnimationStatus(AnimationStatus::Right);

    _DIRECTION d = move.step();
    if (animationStatus == AnimationStatus::Left || animationStatus == AnimationStatus::Right)
    {
        if (d == _DIRECTION::LEFT)
            changeAnimationStatus(AnimationStatus::Left);
        else if (d == _DIRECTION::RIGHT)
            changeAnimationStatus(AnimationStatus::Right);
    }
    
}


sf::RectangleShape Ghost::getShape()
{
    return ghost;
}


AnimationStatus Ghost::getStatus()
{
    return animationStatus;
}