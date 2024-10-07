#include "CollisionShape.h"

namespace acro {

	void CollisionShape::setPosition(const Vec2& newPosition) {}
	Vec2 CollisionShape::getPosition() const { return Vec2(0,0); }
	float CollisionShape::getRadius() const { return 0; }
	float CollisionShape::getWidth() const { return 0; }
	float CollisionShape::getHeight() const { return 0; }

	CircleShape::CircleShape(float centerX, float centerY, float r) : position(Vec2(centerX, centerY)), radius(r) , CollisionShape(ShapeType::CIRCLE){}

	float CircleShape::getRadius() const { return radius; }

	void CircleShape::setPosition(const Vec2& newPosition) { position = newPosition; }

	Vec2 CircleShape::getPosition() const { return position; }

	float CircleShape::getHeight() const { return 0; }

	float CircleShape::getWidth() const { return 0; }






	RectangleShape::RectangleShape(float posX, float posY, float w, float h) : position(Vec2(posX,posY)), width(w), height(h),
		CollisionShape(ShapeType::RECTANGLE) {}

	float RectangleShape::getHeight() const { return height; }
		
	float RectangleShape::getWidth() const { return width; }

	void RectangleShape::setPosition(const Vec2& newPosition) { position = newPosition; }

	Vec2 RectangleShape::getPosition() const { return position; }

	float RectangleShape::getRadius() const { return 0; }



	


}