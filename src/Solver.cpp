#include "Solver.h"

namespace acro
{
    void Solver::handleCollision(std::vector<RigidBody2D*>& bodies)
    {
        std::set<std::pair<RigidBody2D*, RigidBody2D*>> uniquePairs;
        for (size_t i = 0; i < bodies.size(); ++i) {
            for (size_t j = i + 1; j < bodies.size(); ++j) {
                if (bodies[i] && bodies[j]) {  
                    uniquePairs.insert({ bodies[i], bodies[j] });
                }
            }
        }

        for (const auto& pair : uniquePairs) {
            if (!pair.first || !pair.second) continue;  

            if (pair.first->GetShapeType() == acro::ShapeType::CIRCLE && pair.second->GetShapeType() == acro::ShapeType::CIRCLE)
                resolveForCircleAndCircle(pair.first, pair.second);
            else if (pair.first->GetShapeType() == acro::ShapeType::RECTANGLE && pair.second->GetShapeType() == acro::ShapeType::CIRCLE)
                resolveForCircleAndRect(pair.second, pair.first);
            else if (pair.first->GetShapeType() == acro::ShapeType::CIRCLE && pair.second->GetShapeType() == acro::ShapeType::RECTANGLE)
                resolveForCircleAndRect(pair.first, pair.second);
            else
                resolveForRectAndRect(pair.first, pair.second);
        }
    }

    void Solver::resolveForCircleAndCircle(RigidBody2D* firstBody, RigidBody2D* secondBody)
    {
        if (!firstBody || !secondBody || !firstBody->collisionShape || !secondBody->collisionShape) return;  // nullptr kontrolü

        Vec2 pos1 = firstBody->position;
        Vec2 pos2 = secondBody->position;

        Vec2 collisionVector = pos1 - pos2;
        float distance = pos1.distance(pos2);
        float minDistance = firstBody->collisionShape->getRadius() + secondBody->collisionShape->getRadius();

        if (distance < minDistance) {
            float overlap = minDistance - distance;
            Vec2 collisionNormal = collisionVector.normalized();
            Vec2 correctionVector = collisionNormal * (overlap / 2);

            float mass1 = firstBody->mass;
            float mass2 = secondBody->mass;

            Vec2 velocity1 = firstBody->velocity;
            Vec2 velocity2 = secondBody->velocity;

            float v1Normal = velocity1.dot(collisionNormal);
            float v2Normal = velocity2.dot(collisionNormal);

            float momentum1 = (v1Normal * (mass1 - mass2) + 2 * mass2 * v2Normal) / (mass1 + mass2);
            float momentum2 = (v2Normal * (mass2 - mass1) + 2 * mass1 * v1Normal) / (mass1 + mass2);

            Vec2 newVelocity1 = velocity1 + collisionNormal * (momentum1 - v1Normal);
            Vec2 newVelocity2 = velocity2 + collisionNormal * (momentum2 - v2Normal);

            //firstBody->velocity = newVelocity1;
            //secondBody->velocity = newVelocity2;

            if (!firstBody->isStatic) firstBody->position += correctionVector;
            if (!secondBody->isStatic) secondBody->position -= correctionVector;
        }
    }

    void Solver::resolveForCircleAndRect(RigidBody2D* circleBody, RigidBody2D* rectBody)
    {
        if (!circleBody || !rectBody || !circleBody->collisionShape || !rectBody->collisionShape) return;  // nullptr kontrolü

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
            Vec2 collisionNormal = collisionVector.normalized();
            Vec2 correctionVector = collisionNormal * (overlap / 2);

            Vec2 velocity1 = circleBody->velocity;
            Vec2 velocity2 = rectBody->velocity;

            float v1Normal = velocity1.dot(collisionNormal);
            float v2Normal = velocity2.dot(collisionNormal);

            float restitution = (circleBody->restitution + rectBody->restitution) / 2.0f;
            float impulse = (-(1 + restitution) * (v1Normal - v2Normal)) / (1 / circleBody->mass + 1 / rectBody->mass);

            if (!circleBody->isStatic) {
                circleBody->velocity += collisionNormal * (impulse / circleBody->mass);
                circleBody->position -= correctionVector;
            }
            if (!rectBody->isStatic) {
                rectBody->velocity -= collisionNormal * (impulse / rectBody->mass);
                rectBody->position += correctionVector;
            }
        }
    }

    void Solver::resolveForRectAndRect(RigidBody2D* firstBody, RigidBody2D* secondBody)
    {
        if (!firstBody || !secondBody || !firstBody->collisionShape || !secondBody->collisionShape) return;

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

            Vec2 velocity1 = firstBody->velocity;
            Vec2 velocity2 = secondBody->velocity;

            Vec2 collisionNormal = (fabs(overlapX) < fabs(overlapY)) ? Vec2(1, 0) : Vec2(0, 1);

            float v1Normal = velocity1.dot(collisionNormal);
            float v2Normal = velocity2.dot(collisionNormal);

            float restitution = (firstBody->restitution + secondBody->restitution) / 2.0f;
            float impulse = (-(1 + restitution) * (v1Normal - v2Normal)) / (1 / firstBody->mass + 1 / secondBody->mass);

            if (!firstBody->isStatic) {
                firstBody->velocity += collisionNormal * (impulse / firstBody->mass);
            }
            if (!secondBody->isStatic) {
                secondBody->velocity -= collisionNormal * (impulse / secondBody->mass);
            }

            if (overlapX < overlapY) {
                if (!firstBody->isStatic) pos1.x += (center1.x < center2.x) ? -overlapX / 2 : overlapX / 2;
                if (!secondBody->isStatic) pos2.x += (center1.x < center2.x) ? overlapX / 2 : -overlapX / 2;
            }
            else {
                if (!firstBody->isStatic) pos1.y += (center1.y < center2.y) ? -overlapY / 2 : overlapY / 2;
                if (!secondBody->isStatic) pos2.y += (center1.y < center2.y) ? overlapY / 2 : -overlapY / 2;
            }
        }
    }
}