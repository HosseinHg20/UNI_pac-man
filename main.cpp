#include <SFML/Graphics.hpp>
#include <iostream>
#include <pacman/Animation.hpp>
#include <pacman/pacman.hpp>
#include <pacman/map.hpp>


// enum class DIRECTION {LEFT, RIGHT, UP, DOWN};

// class Pacman
// {
// private:
//     sf::Texture texture[2];
//     sf::CircleShape pacman;
//     int mood = 0;

//     int delay = 10;
//     int counter = 0;

//     int netro = 0;

//     DIRECTION dir = DIRECTION::RIGHT;

// public:
//     Pacman(float r = 32.0) : pacman(r)
//     {
//         pacman.setOrigin(sf::Vector2f(r , r));
//         pacman.setPosition(sf::Vector2f(100, 100));

//         texture[0].loadFromFile("./images/pacman1.png");
//         texture[1].loadFromFile("./images/pacman2.png");

//         pacman.setTexture(&texture[mood]);
//     }
//     void setDelay(int d) {delay = d;}
//     sf::CircleShape getShape() {return pacman;}
//     void animation()
//     {
//         if (counter < delay)
//         {
//             counter++;
//             return;
//         }
//         counter = 0;

//         if (mood == 0) // || mood == 1 || mood == 2
//             mood++;
//         else
//             mood = 0;
//         pacman.setTexture(&texture[mood]);
//     }
//     void move()
//     {
//         if (counter < delay)
//             return;

//         switch (dir)
//         {
//         case DIRECTION::RIGHT:
//             pacman.move(sf::Vector2f(1, 0));
//             break;
//         default:
//         case DIRECTION::LEFT:
//             pacman.move(sf::Vector2f(-1, 0));
//             break;
//         case DIRECTION::UP:
//             pacman.move(sf::Vector2f(0, -1));
//             break;
//         case DIRECTION::DOWN:
//             pacman.move(sf::Vector2f(0, 1));
//             break;
//         }
//     }
    
//     void rotate(DIRECTION inputDir)
//     {
//         switch (dir)
//         {
//         case DIRECTION::UP:
//             pacman.rotate(90.0);
//             break;
//         case DIRECTION::LEFT:
//             pacman.rotate(180.0);
//             break;
//         case DIRECTION::DOWN:
//             pacman.rotate(-90.0);
//             break;
//         }
//         dir = DIRECTION::RIGHT;

//         switch (inputDir)
//         {
//         case DIRECTION::UP:
//             pacman.rotate(-90.0);
//             break;
//         case DIRECTION::LEFT:
//             pacman.rotate(180.0);
//             break;
//         case DIRECTION::DOWN:
//             pacman.rotate(90.0);
//             break;
//         }
//         dir = inputDir;
//     }
//     void setNetro(int n) {netro = n; delay = 0;}
//     void fnetro()
//     {
//         if (netro == 0)
//         {
//             return;
//         }

//         netro--;

//         if (netro == 0)
//         {
//             delay = 10;
//         }
        
//     }
// };


int main()
{
    int width = 672;
    int height = 672;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    window.setFramerateLimit(60);
    // sf::CircleShape shape(100.f, 3);
    // shape.setFillColor(sf::Color::Green);
    // shape.setOutlineColor(sf::Color::Blue);
    // shape.setOutlineThickness(29);

    // sf::RectangleShape shape2(sf::Vector2f(50, 20));
    // shape2.setFillColor(sf::Color::Red);

    // sf::ConvexShape shape3;
    // shape3.setPointCount(3);
    // shape3.setPoint(0, sf::Vector2f(100, 10));
    // shape3.setPoint(1, sf::Vector2f(200, 10));
    // shape3.setPoint(2, sf::Vector2f(100, 100));
    

    // sf::CircleShape wall(5.0, 4);
    // wall.setPosition(sf::Vector2f(200, 50));

    // sf::RectangleShape r(sf::Vector2f(64, 64));
    // r.move(sf::Vector2f(200, 200));
    // sf::Texture tex;
    // tex.loadFromFile("./images/pacman1.png");
    // r.setTexture(&tex);
    // Animation anim(&r, "./images/pacman1.png", 0.1);
    // anim.addTextur("./images/pacman2.png");
    // anim.addTextur("./images/pacman3.png");
    // anim.addTextur("./images/pacman4.png");
    // anim.addTextur("./images/pacman5.png");
    // anim.addTextur("./images/pacman6.png");

    Pacman pacmann(0.01, height / 42);
    Map map(height, width);

    // sf::RectangleShape wall(sf::Vector2f(100, 200));
    // wall.setPosition(200, 200);
    // wall.setFillColor(sf::Color::Red);


    sf::Clock clock;
    while (window.isOpen())
    {
        // window.setTitle(std::to_string(static_cast<int>(clock.getElapsedTime().asSeconds())));
        sf::Event event;
        
        int acc = map.accident(pacmann.getShape());
        if (acc > 0)
        {
            pacmann.back();
        }
        else if (acc < 0)
        {
            pacmann.scorePlus(-acc);
            window.setTitle(std::to_string(pacmann.getScore()));
        }
        

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                // window.setTitle("A");
                pacmann.rotate(DIRECTION::LEFT);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                // window.setTitle("W");
                pacmann.rotate(DIRECTION::UP);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                // window.setTitle("D");
                pacmann.rotate(DIRECTION::RIGHT);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                // window.setTitle("S");
                pacmann.rotate(DIRECTION::DOWN);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                // window.setTitle("space");
                pacmann.stop(false);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
            {
                // window.setTitle("space");
                pacmann.stop(true);
            }
            
        //     switch (event.type)
        //     {
        //     case sf::Event::Closed:
        //         window.close();
        //         break;
        //     case sf::Event::KeyPressed:
        //         if (event.key.code == sf::Keyboard::A)
        //         {
        //             shape.setPointCount(shape.getPointCount() + 1);
        //         }
        //         if (event.key.code == sf::Keyboard::D)
        //         {
        //             shape.setPointCount(shape.getPointCount() - 1);
        //         }
        //         if (event.key.code == sf::Keyboard::S)
        //         {
        //             // sf::Vector2f v = shape3.getPosition();
        //             // shape3.setPosition(sf::Vector2f(v.x + 2, v.y));
        //             shape3.move(sf::Vector2f(1, 0));
        //         }
        //         if (event.key.code == sf::Keyboard::F)
        //         {
        //             shape3.rotate(180);
        //         }
        //         if (event.key.code == sf::Keyboard::G)
        //         {
        //             shape.scale(sf::Vector2f(4, 2));
        //         }
                
        //         break;
        //     default:
        //         break;
        //     }
        //     if (event.type == sf::Event::Closed)
        //         window.close();
        }

        // pp.animation();
        // pp.move();
        // anim.update();
        pacmann.update();
        // if (pacmann.getShape().getGlobalBounds().intersects(wall.getGlobalBounds()))
        // {
        //     pacmann.back();
        // }
        
        
        
        
        // pp.fnetro();

        window.clear();
        map.draw(window);
        // window.draw(shape);
        // window.draw(shape2);
        // window.draw(shape3);
        // window.draw(pp.getShape());
        // // window.draw(r);
        // window.draw(wall);
        window.draw(pacmann.getShape());
        window.display();
    }

    return 0;
}