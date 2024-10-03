#include <iostream>
#include "AcroPhysics.h"
#include <SFML/Graphics.hpp>

void main()
{
	acro::PhysicsWorld2D world;

	acro::RigidBody2D body(acro::Vec2(0, 0), acro::Vec2(0, 0), 0.5f,true);
	acro::RigidBody2D body2(acro::Vec2(500, 500), acro::Vec2(0, 0), 50.0f,true);
    
    body.setCollisionShape(10);
    body2.setCollisionShape(10);


	world.addBody(&body);
	world.addBody(&body2);


    sf::RenderWindow window(sf::VideoMode(1280, 720), "Ecro Physics Demo");
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Green);
    sf::CircleShape shape2(10.f);
    shape2.setFillColor(sf::Color::Red);

    sf::Clock clock;  
    float deltaTime;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                body.applyForce(1000,1000);
                std::cout << "Space pressed" << std::endl;
            }
        }

        deltaTime = clock.restart().asSeconds();

        //body.applyForce(100,100);
        //body2.applyForce(20, 60);

        world.update(deltaTime);

        window.clear();
        shape.setPosition(body.position.x,body.position.y);
        shape2.setPosition(body2.position.x,body2.position.y);

        window.draw(shape);
        window.draw(shape2);
        window.display();
    }



}