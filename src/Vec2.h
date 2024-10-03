#pragma once
#include <cmath>

namespace acro {
	class Vec2
	{
	public:
		float x, y;

		Vec2(float x = 0, float y = 0);
		Vec2();

		Vec2 operator+(const Vec2& other) const;
		Vec2& operator+=(const Vec2& other);
		Vec2 operator-(const Vec2& other) const;
		Vec2& operator-=(const Vec2& other);
		Vec2 operator*(const Vec2& other) const;
		Vec2 operator*(float other) const;
		Vec2& operator*=(const Vec2& other);
		Vec2 operator/(const Vec2& other) const;
		Vec2 operator/(float other) const;
		Vec2& operator/=(const Vec2& other);
		Vec2 operator-() const;
		Vec2 normalize() const;
		bool operator==(const Vec2& other) const;
		bool operator!=(const Vec2& other) const;
		float mangitude() const;
		float dot(const Vec2& other);
		float angleBetween(const Vec2& other);
		float distance(const Vec2& other) const;


	};
}

