#include "Vec2.h"

namespace acro {

	Vec2::Vec2(float x, float y) : x(x), y(y) {}
	Vec2::Vec2() : x{0}, y{0} {}

	Vec2 Vec2::operator+(const Vec2& other) const
	{
		return Vec2(x + other.x, y + other.y);
	}

	Vec2& Vec2::operator+=(const Vec2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2 Vec2::operator-(const Vec2& other) const
	{
		return Vec2(x - other.x, y - other.y);
	}

	Vec2& Vec2::operator-=(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vec2 Vec2::operator*(const Vec2& other) const
	{
		return Vec2(x * other.x, y * other.y);
	}
	
	Vec2 Vec2::operator*(const float other) const
	{
		return Vec2(x * other, y * other);
	}

	Vec2& Vec2::operator*=(const Vec2& other) 
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vec2& Vec2::operator*=(const float other)
	{
		x *= other;
		y *= other;
		return *this;
	}

	Vec2 Vec2::operator/(const Vec2& other) const
	{
		if (other.x == 0 || other.y == 0) throw std::invalid_argument("Division by zero");
		return Vec2(x / other.x, y / other.y);
	}

	Vec2 Vec2::operator/(const float other) const
	{
		if (other == 0) throw std::invalid_argument("Division by zero");
		return Vec2(x / other, y / other);
	}

	Vec2& Vec2::operator/=(const Vec2& other)
	{
		if (other.x == 0 || other.y == 0) throw std::invalid_argument("Division by zero");
		x /= other.x;
		y /= other.y;
		return *this;
	}

	Vec2& Vec2::operator/=(const float other)
	{
		if (other == 0) throw std::invalid_argument("Division by zero");
		x /= other;
		y /= other;
		return *this;
	}

	bool Vec2::operator==(const Vec2& other) const
	{
		
		return fabs(x - other.x) < epsilon && fabs(y - other.y) < epsilon;
	}

	bool Vec2::operator!=(const Vec2& other) const
	{
		return !(*this == other);
	}

	Vec2 Vec2::operator-() const
	{
		return Vec2(-x, -y);
	}

	float Vec2::magnitude() const
	{
		return sqrt(x*x + y*y);
	}

	Vec2 Vec2::normalized() const
	{
		float mag = magnitude();
		if (mag < 1e-5f) return Vec2(0,0); 
		return Vec2(x / mag, y / mag);
	}

	float Vec2::dot(const Vec2& other) const
	{
		return x * other.x + y * other.y;
	}

	float Vec2::cross(const Vec2& other) const
	{
		return x * other.y - y * other.x;
	}

	float Vec2::angleBetween(const Vec2& other) const
	{
		float dotProd = dot(other);
		float mags = magnitude() + other.magnitude();
		return acos(dotProd / mags);
	}

	float Vec2::distance(const Vec2& other) const
	{
		return sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y));
	}

	float* Vec2::getArray() const
	{
		static float arr[2] = { x,y };
		return arr;
	}

}