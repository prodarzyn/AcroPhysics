#include "RigidBody2D.h"

namespace acro {
	RigidBody2D::RigidBody2D(Vec2 pos, Vec2 vel, float m) : position(pos), velocity(vel), mass(m), force(0, 0) {}
	RigidBody2D::RigidBody2D(const RigidBody2D& other) = default;

	void RigidBody2D::applyForce(const Vec2& f)
	{
		force += f;
	}

	void RigidBody2D::update(float deltaTime)
	{
		Vec2 acceleration = force * (1.0f/mass);
		velocity += acceleration* deltaTime;

		position += velocity * deltaTime;
		force = Vec2(0, 0);
	}
}