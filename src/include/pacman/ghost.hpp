#ifndef GHOST_HPP
#define GHOST_HPP

#include <SFML/Graphics.hpp>
#include <pacman/animation.hpp>
#include <pacman/move.hpp>
#include <pacman/map.hpp>
#include <vector>

enum class AnimationStatus {Left, Right};

class Ghost
{
private:
    Map & map;
    sf::RectangleShape ghost;
    Animation animation_right;
    Animation animation_left;
    AnimationStatus animationStatus = AnimationStatus::Right;
    Move move;
public:
    Ghost(Map & map, float speed);
    ~Ghost();
    void addNewGhost();
    void changeAnimationStatus(AnimationStatus animationStatus);

    void update();
    sf::RectangleShape getShape();
};



#endif // GHOST_HPP