#include <iostream>
#include <vector>
#include "src/AcroPhysics.h"
#include <SFML/Graphics.hpp>

class Circle
{
public:
    acro::RigidBody2D* body;
    sf::CircleShape shp;

    Circle(float posX, float posY)
    {
        body = new acro::RigidBody2D(acro::Vec2(posX, posY), acro::Vec2(0, 0), 1.0f, false, 0.5);
        body->setCollisionShape(50);
        shp = sf::CircleShape(50);
        shp.setOrigin(50, 50);
        shp.setFillColor(sf::Color::Green);
    }

    ~Circle()
    {
        delete body;
    }

    void draw(sf::RenderWindow& window)
    {
        shp.setPosition(sf::Vector2f(body->position.x, body->position.y));
        window.draw(shp);
    }
};

std::vector<Circle*> circles;

void createCircle(float pos_x, float pos_y, acro::PhysicsWorld2D* world)
{
    Circle* newCircle = new Circle(pos_x, pos_y);
    circles.push_back(newCircle);
    world->addBody(newCircle->body);
}

int main() 
{
    acro::PhysicsWorld2D world;

    acro::RigidBody2D body(acro::Vec2(200, 200), acro::Vec2(0, 0), 1.0f, false, 0.5);
    acro::RigidBody2D body2(acro::Vec2(500, 500), acro::Vec2(0, 0), 1.0f, false, 0.5);
    acro::RigidBody2D body3(acro::Vec2(0, 600), acro::Vec2(0, 0), 1.0f, true, 0.0);

    body.setCollisionShape(50, 100);
    body2.setCollisionShape(50, 50);
    body3.setCollisionShape(1280, 120);

    world.addBody(&body);
    world.addBody(&body2);
    world.addBody(&body3);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Ecro Physics Demo");
    sf::RectangleShape shape(sf::Vector2f(50, 100));
    shape.setFillColor(sf::Color::Red);
    sf::RectangleShape shape2(sf::Vector2f(50, 50));
    shape2.setFillColor(sf::Color::Cyan);
    sf::RectangleShape shape3(sf::Vector2f(1280, 120));

    sf::Clock clock;
    float deltaTime;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space && body.isInCollision)
                    body.applyForce(acro::Vec2(0, -5000));
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    createCircle(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, &world); // createCircle çaðrýsý
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            body.applyForce(acro::Vec2(10, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            body.applyForce(acro::Vec2(-10, 0));

        deltaTime = clock.restart().asSeconds();
        world.update(deltaTime);

        window.clear();
        shape.setPosition(body.position.x, body.position.y);
        shape2.setPosition(body2.position.x, body2.position.y);
        shape3.setPosition(body3.position.x, body3.position.y);
        window.draw(shape);
        window.draw(shape2);
        window.draw(shape3);
        for (const auto& circle : circles)
        {
            circle->draw(window);
        }

        window.display();
    }

    for (auto circle : circles)
    {
        delete circle; 
    }

    return 0; 
}
