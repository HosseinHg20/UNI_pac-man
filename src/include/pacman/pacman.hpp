#ifndef PACMAN_HPP
#define PACMAN_HPP

#include <SFML/Graphics.hpp>
#include <pacman/animation.hpp>
#include <pacman/move.hpp>
#include <pacman/map.hpp>

class Pacman 
{
private:
    Map & map;
    sf::RectangleShape pacman;
    Animation animation;
    Move move;
    int hp = 3;
    int score = 0;

public:
    Pacman(Map & m, float speed = 0.1, int r = 32);
    
    void update();
    sf::RectangleShape & getShape();
    void rotate(DIRECTION dir);
    void back();
    void stop(bool stop);
    void scorePlus(int s);
    int getScore() const;
    int getHP() const;
    int subHP();
    
    void restart(bool map, bool hp, bool score);
};

#endif // PACMAN_HPP