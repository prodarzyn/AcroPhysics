#include "PhysicsWorld2D.h"

namespace acro {
	void PhysicsWorld2D::addBody(RigidBody2D* body)
	{
		bodies.push_back(body);
	}

	void PhysicsWorld2D::update(float deltaTime)
	{
		for (RigidBody2D *body : bodies)
		{
			body->update(deltaTime);
		}
	}

}