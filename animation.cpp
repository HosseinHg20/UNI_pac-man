#include <pacman/animation.hpp>

Animation::Animation(sf::Shape * sh, std::string s, float t)
{
    // setenable(true);
    shape = sh;
    time = sf::seconds(t);
    addTexture(s);
    // update();
    // setenable(false);
    sh->setTexture(&frames[0]);
}

void Animation::addTexture(std::string s)
{
    sf::Texture t;
    if (!t.loadFromFile(s))
        throw 1;
    
    frames.push_back(t);
}

void Animation::update()
{
    if (clock.getElapsedTime().asSeconds() > time.asSeconds() && enable)
    {
        clock.restart();
        if (frame < frames.size() - 1)
            frame++;
        else
            frame = 0;
        shape->setTexture(&frames[frame]);
    }
}


void Animation::setenable(bool en)
{
    enable = en;
    shape->setTexture(&frames[0]);
    frame = 0;
}