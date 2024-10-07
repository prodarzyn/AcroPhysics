#pragma once

struct Material
{
	float density;
	float restitution;
	float staticFriction;
	float dynamicFriction;
	Material(float density, float restitution, float staticFriction, float dynamicFriction) : density(density), restitution(restitution),
		staticFriction(staticFriction), dynamicFriction(dynamicFriction) {}
	Material() : density(1.0f), restitution(0.5f), staticFriction(0.5f), dynamicFriction(0.3f) {}
};

