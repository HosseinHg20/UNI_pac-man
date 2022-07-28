#ifndef GHOSTANIMATION_HPP
#define GHOSTANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <pacman/animation.hpp>
#include <pacman/move.hpp>
#include <pacman/map.hpp>

class RightAnimation : public Animation
{
public:
    RightAnimation(sf::RectangleShape & shape) : Animation(&shape, "./images/ghosts _r_1.png", 0.1)
    {
        addTextur("./images/ghosts _r_2.png");
        setenable(true);
    }
};
class LeftAnimation : public Animation
{
public:
    LeftAnimation(sf::RectangleShape & shape) : Animation(&shape, "./images/ghosts _l_1.png", 0.1)
    {
        addTextur("./images/ghosts _l_2.png");
        setenable(true);
    }
};


#endif // GHOSTANIMATION_HPP