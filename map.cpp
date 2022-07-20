#include <pacman/map.hpp>

Map::Map(int h, int w) : h_block(h / 21), w_block(w / 21) ,
                         leftTeleport(sf::Vector2f(h / 21, w / 21)), rightTeleport(sf::Vector2f(h / 21, w / 21))
{
    std::string strBlocks[]{
        "111111111111111111111",
        "1         1         1",
        "1 111 111 1 111 111 1",
        "1 11             11 1",
        "1    1 1111111 1    1",
        "1 11 1    1    1 11 1",
        "1    1111 1 1111    1",
        "1111 1         1 1111",
        "   1 1 111 111 1 1   ",
        "1111 1 1     1 1 1111",
        "#      1111111      #",
        "1111 1         1 1111",
        "   1 1 1111111 1 1   ",
        "1111 1    1    1 1111",
        "1    1111 1 1111    1",
        "1 11             11 1",
        "1 11 1 1111111 1 11 1",
        "1    1    1    1    1",
        "1 1111111 1 1111111 1",
        "1                   1",
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
            
        }
    }
    
    leftTeleport.setFillColor(sf::Color::White);
    leftTeleport.setPosition(0 * w_block, 10 * h_block);
    rightTeleport.setFillColor(sf::Color::White);
    rightTeleport.setPosition(20 * w_block, 10 * h_block);


}

void Map::draw(sf::RenderWindow & window)
{
    for (int i = 0; i < blocks.size(); i++)
    {
        window.draw(blocks[i]);
    }
    window.draw(leftTeleport);
    window.draw(rightTeleport);
}

int Map::accident(sf::RectangleShape & shape)
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
        shape.setPosition(w_block * 19, h_block * 21 / 2);
        return -1;
    }
    if (shape.getGlobalBounds().intersects(rightTeleport.getGlobalBounds()))
    {
        shape.setPosition(w_block * 2, h_block * 21 / 2);
        return -1;
    }
    
    return 0;
}