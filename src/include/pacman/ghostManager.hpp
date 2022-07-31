#ifndef GHOSTMANAGER_HPP
#define GHOSTMANAGER_HPP

#include <vector>
#include <pacman/ghost.hpp>
#include <pacman/map.hpp>

class GhostManager
{
private:
    std::vector<Ghost *> ghost;
    Map & map;
public:
    GhostManager(Map & m) : map(m) {}
    void addGhost()
    {
        Ghost * g = new Ghost(map, 0.01);
        ghost.push_back(g);
    }
    void update()
    {
        for (int i = 0; i < ghost.size(); i++)
            ghost[i]->update();
    }
    void draw(sf::RenderWindow & window)
    {
        for (int i = 0; i < ghost.size(); i++)
            window.draw(ghost[i]->getShape());
    }
    int accident(sf::RectangleShape shape)
    {
        for (int i = 0; i < ghost.size(); i++)
            if (shape.getGlobalBounds().intersects(ghost[i]->getShape().getGlobalBounds()))
                if (ghost[i]->getStatus() == AnimationStatus::Scared)
                    return -(i + 1);
                else if (ghost[i]->getStatus() == AnimationStatus::DiedLeft || ghost[i]->getStatus() == AnimationStatus::DiedRight)
                    return 0;
                else
                    return (i + 1);
        return 0;
    }
    void backToHome(int number)
    {
        delete ghost[number - 1];
        ghost[number - 1] = new Ghost(map, 0.01);
    }
    void restart()
    {
        for (int i = 0; i < ghost.size(); i++)
        {
            delete ghost[i];
            ghost[i] = new Ghost(map, 0.01);
        }
    }
    void setScare()
    {
        for (int i = 0; i < ghost.size(); i++)
            ghost[i]->changeAnimationStatus(AnimationStatus::Scared);
    }
    ~GhostManager()
    {
        for (int i = 0; i < ghost.size(); i++)
            delete ghost[i];
    }
};

#endif // GHOSTMANAGER_HPP