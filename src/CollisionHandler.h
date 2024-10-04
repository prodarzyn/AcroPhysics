#pragma once
#include "RigidBody2D.h"
#include <vector>
#include <set>
#include <utility>
#include <unordered_set>
#include "CollisionShape.h"
#include <unordered_set>
#include <utility>
namespace acro
{
	class CollisionHandler
	{
	public:
		static void handleCollision(std::vector<RigidBody2D*>& bodies);
	private:
		static bool checkCollision(RigidBody2D* body1, RigidBody2D* body2);
		static void resolveForCircleAndCircle(RigidBody2D* firstBody, RigidBody2D* secondBody);
		static void resolveForCircleAndRect(RigidBody2D* circleBody, RigidBody2D* rectBody);
		static void resolveForRectAndRect(RigidBody2D* firstBody, RigidBody2D* secondBody);


	};
}
