#include "Vec2.h"

namespace acro {
	Vec2::Vec2(float x, float y) : x(x), y(y) {}
	Vec2::Vec2() : x(0), y(0) {};

	Vec2 Vec2::operator+(const Vec2& other) const
	{
		return Vec2(this->x + other.x, this->y + other.y);
	}

	Vec2& Vec2::operator+=(const Vec2& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vec2 Vec2::operator-(const Vec2& other) const
	{
		return Vec2(this->x - other.x, this->y - other.y);
	}

	Vec2& Vec2::operator-=(const Vec2& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Vec2 Vec2::operator*(const Vec2& other) const
	{
		return Vec2(this->x * other.x, this->y * other.y);
	}

	
	Vec2 Vec2::operator*(float other) const
	{
		return Vec2(this->x * other, this->y * other);
	}



	Vec2& Vec2::operator*=(const Vec2& other) 
	{
		this->x *= other.x;
		this->y *= other.y;
		return *this;
	}

	Vec2 Vec2::operator/(const Vec2& other) const
	{
		return Vec2(this->x / other.x, this->y / other.y);
	}

	Vec2 Vec2::operator/(float other) const
	{
		return Vec2(x / other, y / other);
	}

	Vec2& Vec2::operator/=(const Vec2& other)
	{
		this->x /= other.x;
		this->y /= other.y;
		return *this;
	}

	bool Vec2::operator==(const Vec2& other) const
	{
		return this->x == other.x && this->y == other.y;
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

	Vec2 Vec2::normalize() const
	{
		float mag = magnitude();
		return Vec2(x / mag, y / mag);
	}

	float Vec2::dot(const Vec2& other)
	{
		return this->x * other.x + this->y * other.y;
	}

	float Vec2::angleBetween(const Vec2& other)
	{
		float dotProd = dot(other);
		float mags = magnitude() + other.magnitude();
		return acos(dotProd / mags);
	}

	float Vec2::distance(const Vec2& other) const
	{
		return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
	}

}