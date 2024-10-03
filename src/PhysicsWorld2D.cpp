#include "PhysicsWorld2D.h"

namespace acro {
	void PhysicsWorld2D::addBody(RigidBody2D* body)
	{
		bodies.push_back(body);
	}

	void PhysicsWorld2D::update(float deltaTime)
	{
		if (bodies.size() >= 2)
		{
			for (int i = 1; i < bodies.size(); i++)
			{
				
				bodies[0]->checkCollisionWith(bodies[i]);
			}

		}

		for (RigidBody2D *body : bodies)
		{
			body->update(deltaTime*timeScale,gravity);
		}
	}

}