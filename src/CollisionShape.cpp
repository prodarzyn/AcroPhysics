#include "CollisionShape.h"

namespace acro {
	void CollisionShape::setPosition(const Vec2& newPosition) {}

	Vec2 CollisionShape::getPosition() const { return Vec2(0,0); }

	float CollisionShape::getRadius() const { return 0; }
	float CollisionShape::getWidth() const { return 0; }
	float CollisionShape::getHeight() const { return 0; }

	CircleShape::CircleShape(float centerX, float centerY, float r) : position(Vec2(centerX, centerY)), radius(r) {}

	float CircleShape::getRadius() const
	{
		return radius;
	}

	Vec2 CircleShape::getPosition() const
	{
		return position;
	}

	void CircleShape::setPosition(const Vec2& newPosition)
	{
		position = newPosition;
	}

	bool CircleShape::checkCollision(const CollisionShape& other) const
	{
		const CircleShape* circle = dynamic_cast<const CircleShape*>(&other);
		if (circle) {
			float dx = position.x - circle->position.x;
			float dy = position.y - circle->position.y;
			float distance = std::sqrt(dx * dx + dy * dy);
			return distance < (radius + circle->radius);
		}

		const RectangleShape* rectangle = dynamic_cast<const RectangleShape*>(&other);
		if (rectangle) {
			return rectangle->checkCollision(*this);
		}

		return false;
	}



	RectangleShape::RectangleShape(float posX, float posY, float w, float h) : position(Vec2(posX,posY)), width(w), height(h) {}

	float RectangleShape::getHeight() const
	{
		return height;
	}

	float RectangleShape::getWidth() const
	{
		return width;
	}

	Vec2 RectangleShape::getPosition() const
	{
		return position;
	}

	void RectangleShape::setPosition(const Vec2& newPosition)
	{
		position = newPosition;
	}


	bool RectangleShape::checkCollision(const CollisionShape& other) const
	{
		const CircleShape* circle = dynamic_cast<const CircleShape*>(&other);
		if (circle) {
			float closestX = Math::clamp(circle->getPosition().x, position.x, position.x + width);
			float closestY = Math::clamp(circle->getPosition().y, position.y, position.y + height);
			float dx = circle->getPosition().x - closestX;
			float dy = circle->getPosition().y - closestY;
			return (dx * dx + dy * dy) < (circle->getRadius() * circle->getRadius());
		}

		const RectangleShape* rectangle = dynamic_cast<const RectangleShape*>(&other);
		if (rectangle) {
			return !(position.x + width < rectangle->position.x || position.x > rectangle->position.x + rectangle->width ||
				position.y + height < rectangle->position.y || position.y > rectangle->position.y + rectangle->height);
		}

		return false;
	}


}