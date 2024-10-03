#pragma once
#include "RigidBody2D.h"
#include <vector>

namespace acro {
	class PhysicsWorld2D
	{	
	public:
		Vec2 gravity = Vec2(0,9.8);
		float timeScale = 10.0f;
		std::vector<RigidBody2D*> bodies;
		void addBody(RigidBody2D* body);
		void update(float deltaTime);
	};

}