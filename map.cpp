#include <pacman/map.hpp>

Map::Map(int h, int w) : h_block(h / 21), w_block(w / 21) ,
                         leftTeleport(sf::Vector2f(h / 21, w / 21)), rightTeleport(sf::Vector2f(h / 21, w / 21))
{
    srand(time(0));
    _time = sf::seconds(10);

    std::string strBlocks[]{
        "111111111111111111111",
        "1         1         1",
        "1 111 111 1 111 111 1",
        "1 11             11 1",
        "1    1 1111111 1    1",
        "1 11 1    1    1 11 1",
        "1    1111 1 1111    1",
        "1111 1         1 1111",
        "0001 1 1110111 1 1000",
        "1111 1 1000001 1 1111",
        "#      1111111      #",
        "1111 1         1 1111",
        "0001 1 1111111 1 1000",
        "1111 1    1    1 1111",
        "1    1111 1 1111    1",
        "1 11             11 1",
        "1 11 1 1111111 1 11 1",
        "1    1    1    1    1",
        "1 1111111 1 1111111 1",
        "1         0         1",
        "111111111111111111111",
    };
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            if (strBlocks[i][j] == '1')
            {
                sf::RectangleShape block(sf::Vector2f(h_block, w_block));
                block.setFillColor(sf::Color::Blue);
                // block.setOrigin(h_block / 2, w_block / 2);
                block.setPosition(j * w_block, i * h_block);
                blocks.push_back(block);
            }
            if (strBlocks[i][j] == ' ')
            {
                fd::Food food;
                food.setPosition(j * w_block + (w_block / 3), i * h_block + (h_block / 3));
                foods.push_back(food);
            }
        }
    }
    
    leftTeleport.setFillColor(sf::Color::White);
    leftTeleport.setPosition(0 * w_block, 10 * h_block);
    rightTeleport.setFillColor(sf::Color::White);
    rightTeleport.setPosition(20 * w_block, 10 * h_block);

    visibleFoods = foods.size();

    setRandomFood(fd::Type::Strength);
    setRandomFood(fd::Type::Strength);
    setRandomFood(fd::Type::Strength);
    setRandomFood(fd::Type::Strength);
    setRandomFood(fd::Type::Strength);
}

void Map::draw(sf::RenderWindow & window)
{
    for (int i = 0; i < blocks.size(); i++)
    {
        window.draw(blocks[i]);
    }
    for (int i = 0; i < foods.size(); i++)
    {
        if (foods[i].getVisibility())
            window.draw(foods[i]);
    }
    window.draw(leftTeleport);
    window.draw(rightTeleport);
}

int Map::accident(sf::RectangleShape & shape, bool ghost)
{
    for (int i = 0; i < blocks.size(); i++)
    {
        if (shape.getGlobalBounds().intersects(blocks[i].getGlobalBounds()))
        {
            return i;
        }
    }
    if (shape.getGlobalBounds().intersects(leftTeleport.getGlobalBounds()))
    {
        shape.setPosition(w_block * 19 + 16, h_block * 21 / 2);
        return 0;
    }
    if (shape.getGlobalBounds().intersects(rightTeleport.getGlobalBounds()))
    {
        shape.setPosition(w_block * 2 - 5, h_block * 21 / 2);
        return 0;
    }

    if (ghost)
        return 0;

    for (int i = 0; i < foods.size(); i++)
    {
        if (shape.getGlobalBounds().intersects(foods[i].getGlobalBounds()) && foods[i].getVisibility())
        {
            foodCounter++;
            visibleFoods--;
            foods[i].setVisibility(false);
            if (foods[i].getType() == fd::Type::Normal)
                return -10;
            if (foods[i].getType() == fd::Type::Strength)
                return -50;
            
            specialFoodNumber = -1;
            if (foods[i].getType() == fd::Type::Apple)
                return -100;
            
        }
    }
    
    return 0;
}

void Map::setRandomFood(fd::Type t)
{
    int r = rand() / foods.size();
    if (t == fd::Type::Strength || t == fd::Type::Normal)
    {
        foods[r].change(t);
    }
    else if (specialFoodNumber == -1)
    {
        if (!foods[r].getVisibility())
            visibleFoods++;
        _clock.restart();
        foods[r].setVisibility(true);
        foods[r].change(t);
        specialFoodNumber = r;
    }
}

void Map::checkSpecoalFood()
{
    if (_clock.getElapsedTime().asSeconds() > _time.asSeconds() && specialFoodNumber != -1)
    {
        _clock.restart();
        foods[specialFoodNumber].change(fd::Type::Normal);
        specialFoodNumber = -1;
    }
}

int Map::getFoodCounter()
{
    return foodCounter;
}
int Map::getVisibleFoods()
{
    return visibleFoods;
}

void Map::restart()
{
    for (int i = 0; i < foods.size(); i++)
    {
        foods[i].setVisibility(true);
    }
    visibleFoods = foods.size();

    setRandomFood(fd::Type::Strength);
    setRandomFood(fd::Type::Strength);
    setRandomFood(fd::Type::Strength);
    setRandomFood(fd::Type::Strength);
    setRandomFood(fd::Type::Strength);
    
    
    foodCounter = 0;
    specialFoodNumber = -1;
    _clock.restart();
}