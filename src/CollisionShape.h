#pragma once
#include "Vec2.h"
#include "Math.h"
#include <algorithm>

namespace acro {
	class CollisionShape
	{
	public:
		virtual bool checkCollision(const CollisionShape& other) const = 0;
		virtual void setPosition(const Vec2& newPosition);
		virtual Vec2 getPosition() const;
		virtual float getRadius() const;
		virtual float getWidth() const;
		virtual float getHeight() const;
	};

	class CircleShape : public CollisionShape
	{
	public:

		CircleShape(float centerX, float centerY, float r);

		bool checkCollision(const CollisionShape& other) const override;
		float getRadius() const override;
		float getWidth() const override;
		float getHeight() const override;
		Vec2 getPosition() const override;
		void setPosition(const Vec2& newPosition) override;
	private:
		Vec2 position = Vec2(0, 0);
		float radius;
	};

	class RectangleShape : public CollisionShape
	{
	public:

		RectangleShape(float posX, float posY, float w, float h);
		bool checkCollision(const CollisionShape& other) const override;
		Vec2 getPosition() const override;
		float getWidth() const override;
		float getHeight() const override;
		float getRadius() const override;
		void setPosition(const Vec2& newPosition) override;
		
	private:
		float width, height;
		Vec2 position = Vec2(0, 0);
	};
}


