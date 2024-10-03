#pragma once
#include "Vec2.h"
#include <iostream>

namespace acro {

	class RigidBody2D
	{
	public:
		Vec2 position;
		Vec2 velocity;
		Vec2 force;
		float mass;

		RigidBody2D(Vec2 pos, Vec2 vel, float m);
		RigidBody2D(const RigidBody2D& other);
		void applyForce(const Vec2& f);
		void update(float deltaTime);

	};
}
