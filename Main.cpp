#include <iostream>
#include "AcroPhysics.h"
#include <chrono>
#include <thread>

void main()
{
	acro::PhysicsWorld2D world;

	acro::RigidBody2D body(acro::Vec2(0, 0), acro::Vec2(0, 0), 1.0f);


	world.addBody(&body);

    acro::Clock clock;



    while (true) {
		float dt = clock.getDeltaTime();
		
		world.update(dt);

		body.applyForce(acro::Vec2(100.0f, 100.0f));

		std::cout << body.position.x << " , " << body.position.y << std::endl;

		clock.sleepForFrame();
    }
}