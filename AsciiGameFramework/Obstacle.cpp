#include "Obstacle.h"

Obstacle::Obstacle(const int xPos, const int yPos, const Direction moveDir, const float moveSpeed)
    : MovingStraightObject(xPos, yPos, moveDir, moveSpeed)
{
    model = CreteModelUsingChar(219,4,2);
}

void Obstacle::OnCollisionEnter(CollidingObject* other, Direction collisionDirection)
{
    if (TimeUtils::Instance().GetTime() - lastTimeMovedInGrid < 2)
        AudioManager::Instance().PlayFx("hit.wav", 0.2);
}
