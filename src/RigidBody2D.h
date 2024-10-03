#pragma once
#include "Vec2.h"
#include <iostream>
#include "CollisionShape.h"


namespace acro {

	class RigidBody2D
	{
	public:
		Vec2 position;
		Vec2 velocity;
		Vec2 force;
		float mass;
		bool isStatic;
		float restitution;

		RigidBody2D(Vec2 pos, Vec2 vel, float m,bool isStatic = false, float restitution = 1.0);
		RigidBody2D(const RigidBody2D& other);
		~RigidBody2D();
		void applyForce(const Vec2& f);
		void applyForce(float x, float y);
		void update(float deltaTime, const Vec2& gravity);
		void setCollisionShape(float radius);
		void setCollisionShape(float width,float height);
		void checkCollisionWith(RigidBody2D* other);
		void resolveCollision(RigidBody2D* other);

	private:
		CollisionShape* collisionShape;

	};
}
