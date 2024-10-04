#include "CollisionHandler.h"


namespace acro
{
	bool CollisionHandler::checkCollision(RigidBody2D* body1, RigidBody2D* body2)
	{
        if (body1->collisionShape && body1->collisionShape->checkCollision(*body2->collisionShape))
        {
            body1->isInCollision = true;
            body2->isInCollision = true;
            return true;
        }
        body1->isInCollision = false;
        body2->isInCollision = false;
		return false;
	}

	void CollisionHandler::handleCollision(std::vector<RigidBody2D*>& bodies)
	{
        //finding unique pairs
		std::set<std::pair<RigidBody2D*, RigidBody2D*>> uniquePairs;
		for (size_t i = 0; i < bodies.size(); ++i) {
			for (size_t j = i + 1; j < bodies.size(); ++j) {
				uniquePairs.insert({ bodies[i], bodies[j] });
			}
		}

        //Resolving different collision types
		for (const auto& pair : uniquePairs) {
			if (checkCollision(pair.first, pair.second)) {
                if (pair.first->collisionShape->getRadius() != 0 && pair.second->collisionShape->getRadius() != 0)
                    resolveForCircleAndCircle(pair.first, pair.second);
                else if (pair.first->collisionShape->getRadius() == 0 && pair.second->collisionShape->getRadius() != 0)
                    resolveForCircleAndRect(pair.second, pair.first);
                else if (pair.first->collisionShape->getRadius() != 0 && pair.second->collisionShape->getRadius() == 0)
                    resolveForCircleAndRect(pair.first, pair.second);
                else
                    resolveForRectAndRect(pair.first, pair.second);
                    
			}
		}
	}

    void CollisionHandler::resolveForCircleAndCircle(RigidBody2D* firstBody, RigidBody2D* secondBody)
    {
        Vec2 pos1 = firstBody->position; 
        Vec2 pos2 = secondBody->position;

        Vec2 collisionVector = pos2 - pos1;
        float distance = pos1.distance(pos2);

        float minDistance = firstBody->collisionShape->getRadius() + secondBody->collisionShape->getRadius();

        if (distance < minDistance) {
            float overlap = minDistance - distance;

            Vec2 correctionVector = collisionVector.normalize() * (overlap / 2);

            pos1 -= correctionVector;
            pos2 += correctionVector;


            Vec2 velocity1 = firstBody->velocity;
            Vec2 velocity2 = secondBody->velocity;

            Vec2 collisionNormal = collisionVector.normalize();

            float v1Normal = velocity1.dot(collisionNormal);
            float v2Normal = velocity2.dot(collisionNormal);

            if (v1Normal < 0 && v2Normal > 0) {
                return; 
            }

            float restitution = (firstBody->restitution + secondBody->restitution) / 2.0f; 
            float impulse = (-(1 + restitution) * (v1Normal - v2Normal)) / (1 / firstBody->mass + 1 / secondBody->mass);

            if (!firstBody->isStatic)
            {
                firstBody->position = pos1;
                firstBody->velocity += collisionNormal * (impulse / firstBody->mass);
            }
               
            if (!secondBody->isStatic)
            {
                secondBody->position = pos2;
                secondBody->velocity -= collisionNormal * (impulse / secondBody->mass);
            }
                
        }
    }

    void CollisionHandler::resolveForCircleAndRect(RigidBody2D* circleBody, RigidBody2D* rectBody)
    {

        Vec2 circlePos = circleBody->position; 
        Vec2 rectPos = rectBody->position;    

        float circleRadius = circleBody->collisionShape->getRadius();

        float rectHalfWidth = rectBody->collisionShape->getWidth() / 2.0f; 
        float rectHalfHeight = rectBody->collisionShape->getHeight() / 2.0f; 

        Vec2 rectCenter = rectPos + Vec2(rectHalfWidth, rectHalfHeight);

        Vec2 difference = circlePos - rectCenter;

        float closestX = std::max(-rectHalfWidth, std::min(difference.x, rectHalfWidth));
        float closestY = std::max(-rectHalfHeight, std::min(difference.y, rectHalfHeight));

        Vec2 closestPoint = rectCenter + Vec2(closestX, closestY);

        Vec2 collisionVector = closestPoint - circlePos;
        float distance = collisionVector.magnitude();

        if (distance < circleRadius) {
            float overlap = circleRadius - distance;

            Vec2 collisionNormal = collisionVector.normalize();

            Vec2 correctionVector = collisionNormal * (overlap / 2);


            Vec2 velocity1 = circleBody->velocity;
            Vec2 velocity2 = rectBody->velocity;

            float v1Normal = velocity1.dot(collisionNormal);
            float v2Normal = velocity2.dot(collisionNormal);

            if (v1Normal < 0 && v2Normal > 0) {
                return;
            }

            float restitution = (circleBody->restitution + rectBody->restitution) / 2.0f; 
            float impulse = (-(1 + restitution) * (v1Normal - v2Normal)) / (1 / circleBody->mass + 1 / rectBody->mass);

            if (!circleBody->isStatic)
            {
                circleBody->position -= correctionVector;
                circleBody->velocity += collisionNormal * (impulse / circleBody->mass);

            }
                
            if(!rectBody->isStatic)
            {
                rectBody->position += correctionVector;
                rectBody->velocity -= collisionNormal * (impulse / rectBody->mass);
            }

        }
    }

    void CollisionHandler::resolveForRectAndRect(RigidBody2D* firstBody, RigidBody2D* secondBody)
    {

        Vec2 pos1 = firstBody->position;  
        Vec2 pos2 = secondBody->position; 

        float halfWidth1 = firstBody->collisionShape->getWidth() / 2.0f;
        float halfHeight1 = firstBody->collisionShape->getHeight() / 2.0f;
        float halfWidth2 = secondBody->collisionShape->getWidth() / 2.0f;
        float halfHeight2 = secondBody->collisionShape->getHeight() / 2.0f;

        Vec2 center1 = pos1 + Vec2(halfWidth1, halfHeight1);
        Vec2 center2 = pos2 + Vec2(halfWidth2, halfHeight2);

        if (fabs(center1.x - center2.x) <= halfWidth1 + halfWidth2 &&
            fabs(center1.y - center2.y) <= halfHeight1 + halfHeight2)
        {
            float overlapX = (halfWidth1 + halfWidth2) - fabs(center1.x - center2.x);
            float overlapY = (halfHeight1 + halfHeight2) - fabs(center1.y - center2.y);

            if (overlapX < overlapY) {
                if (center1.x < center2.x) {
                    pos1.x -= overlapX / 2;
                    pos2.x += overlapX / 2;
                }
                else {
                    pos1.x += overlapX / 2;
                    pos2.x -= overlapX / 2;
                }
            }
            else {
                if (center1.y < center2.y) {
                    pos1.y -= overlapY / 2;
                    pos2.y += overlapY / 2;
                }
                else {
                    pos1.y += overlapY / 2;
                    pos2.y -= overlapY / 2;
                }
            }


            Vec2 velocity1 = firstBody->velocity;
            Vec2 velocity2 = secondBody->velocity;

            Vec2 collisionNormal = (fabs(overlapX) < fabs(overlapY)) ? Vec2(1, 0) : Vec2(0, 1);

            float v1Normal = velocity1.dot(collisionNormal);
            float v2Normal = velocity2.dot(collisionNormal);

            if (v1Normal < 0 && v2Normal > 0) {
                return; 
            }

            float restitution = (firstBody->restitution + secondBody->restitution) / 2.0f;
            float impulse = (-(1 + restitution) * (v1Normal - v2Normal)) / (1 / firstBody->mass + 1 / secondBody->mass);

            if (!firstBody->isStatic)
            {
                firstBody->position = pos1;
                firstBody->velocity += collisionNormal * (impulse / firstBody->mass);
            }
               
            if (!secondBody->isStatic)
            {
                secondBody->position = pos2;
                secondBody->velocity -= collisionNormal * (impulse / secondBody->mass);
            }
            
        }
    }

    

}
