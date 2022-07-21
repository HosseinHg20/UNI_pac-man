#ifndef FOOD_HPP
#define FOOD_HPP

#include <SFML/Graphics.hpp>

namespace fd
{
    
enum class Type {Normal, Strength, Apple};

class Food : public sf::CircleShape
{
private:
    Type type;
    bool visible = true;
    sf::Texture txtapple;
public:
    Food();

    void change(Type t);
    Type getType();
    void setVisibility(bool v);
    bool getVisibility();
};

} // namespace Fd

#endif // FOOD_HPP
