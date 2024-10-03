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

	void RigidBody2D::checkCollisionWith(RigidBody2D* other) {
		if (collisionShape && collisionShape->checkCollision(*other->collisionShape)) {
			std::cout << "Collision detected!" << std::endl;
			resolveCollision(other);
		}
		else {
			std::cout << "No collision." << std::endl;
		}
	}

	void RigidBody2D::resolveCollision(RigidBody2D* other) {
		
		Vec2 pos2 = other->position;

		
		Vec2 collisionVector = pos2 - position;
		float distance = position.distance(pos2);

		float minDistance = collisionShape->getRadius() + other->collisionShape->getRadius();

		if (distance <= minDistance) {
			float overlap = minDistance - distance;

			Vec2 correctionVector = collisionVector.normalize() * overlap / 2;

			position = position - correctionVector;
			other->position = pos2 + correctionVector;

			Vec2 velocity2 = other->velocity;

			Vec2 collisionNormal = collisionVector.normalize();

			float v1Normal = velocity.dot(collisionNormal);
			float v2Normal = velocity2.dot(collisionNormal);

			float momentumDiff = (v1Normal * (mass - 0.0 * other->mass) + v2Normal * (other->mass + 0.0 * mass)) / (mass + other->mass);

			if (!other->isStatic)
			{
				velocity = velocity - collisionNormal * momentumDiff;
				velocity = (mass > other->mass) ? velocity : -velocity;
				return;
			}
			
			velocity = velocity - collisionNormal;
			other->velocity = velocity2 + collisionNormal * momentumDiff;

		}


	}

	void RigidBody2D::update(float deltaTime,const Vec2& gravity)
	{
		Vec2 acceleration = force * (1.0f/mass);
		if (!isStatic)
			acceleration += gravity * (1.0f/mass);
		velocity += acceleration * deltaTime;

		position += velocity * deltaTime;
		if(collisionShape)
			collisionShape->setPosition(position);

		force = Vec2(0, 0);
	}
}