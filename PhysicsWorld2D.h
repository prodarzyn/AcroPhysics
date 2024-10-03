#pragma once
#include "RigidBody2D.h"
#include <vector>

namespace acro {
	class PhysicsWorld2D
	{
	public:
		std::vector<RigidBody2D*> bodies;
		void addBody(RigidBody2D* body);
		void update(float deltaTime);
	};

}