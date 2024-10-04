#include "RigidBody2D.h"

namespace acro {
	RigidBody2D::RigidBody2D(Vec2 pos, Vec2 vel, float m, bool isStatic,float restitution) : position(pos), velocity(vel), 
		mass(m), force(0, 0), isStatic(isStatic),restitution(restitution){}

	RigidBody2D::RigidBody2D(const RigidBody2D& other) = default;
	
	RigidBody2D::~RigidBody2D()
	{
		delete collisionShape;
	}

	void RigidBody2D::applyForce(const Vec2& f)
	{
		force += f;
	}

	void RigidBody2D::applyForce(float x, float y)
	{
		force += Vec2(x,y);
	}

	void RigidBody2D::setCollisionShape(float radius)
	{
		collisionShape = new CircleShape(position.x,position.y,radius);
	}

	void RigidBody2D::setCollisionShape(float width,float height)
	{
		collisionShape = new RectangleShape(position.x, position.y, width,height);
	}


	void RigidBody2D::update(float deltaTime, const Vec2& gravity)
	{
		Vec2 netForce = (!isStatic) ? (gravity * mass) + force : force;
		Vec2 acceleration = netForce / mass;

		velocity += acceleration * deltaTime;
		if(isInCollision)
			velocity = Vec2(friction*velocity.x,velocity.y);
		position += velocity * deltaTime;
		if (collisionShape)
			collisionShape->setPosition(position);

		force = Vec2(0, 0); 
	}
}