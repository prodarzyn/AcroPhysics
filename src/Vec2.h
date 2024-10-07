#pragma once
#include <cmath>
#include <stdexcept>

namespace acro {
	const float epsilon = 1e-5f;

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
		Vec2 operator*(const float other) const;
		Vec2& operator*=(const Vec2& other);
		Vec2& operator*=(const float other);
		Vec2 operator/(const Vec2& other) const;
		Vec2 operator/(const float other) const;
		Vec2& operator/=(const Vec2& other);
		Vec2& operator/=(const float other);
		Vec2 operator-() const;
		Vec2 normalized() const;
		bool operator==(const Vec2& other) const;
		bool operator!=(const Vec2& other) const;
		float magnitude() const;
		float dot(const Vec2& other) const;
		float cross(const Vec2& other) const;
		float angleBetween(const Vec2& other) const;
		float distance(const Vec2& other) const;
		float* getArray() const;
	};
}

