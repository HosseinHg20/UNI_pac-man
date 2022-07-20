#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Animation
{
private:
    sf::Shape * shape;
    sf::Clock clock;
    sf::Time time;
    int frame = 0;
    std::vector<sf::Texture> frames;
    bool enable = false;
public:
    Animation(sf::Shape * sh, std::string s, float second);

    void addTextur(std::string s);
    void update();
    void setenable(bool en);
};

#endif //ANIMATION_HPP