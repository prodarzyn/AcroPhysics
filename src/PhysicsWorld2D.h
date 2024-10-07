#pragma once
#include "RigidBody2D.h"
#include <vector>
#include "Solver.h"

namespace acro {
	class PhysicsWorld2D
	{	
	public:
		Vec2 gravity = Vec2(0,9.8);
		float timeScale = 10.0f;
		void addBody(RigidBody2D* body);
		void removeBody(RigidBody2D* body);
		void step(float deltaTime);
	private:
		std::vector<RigidBody2D*> bodies;

	};

}