#include "Obstacle.h"
#include "AudioManager.h"
#include "TimeUtils.h"

Obstacle::Obstacle(int xPos, int yPos, Direction moveDir, float moveSpeed)
    : MovingStraightObject(xPos, yPos, moveDir, moveSpeed)
{
    model = CreteModelUsingChar(219,4,2);
}

void Obstacle::OnCollisionEnter(CollidingObject* other, Direction collisionDirection)
{
    if (TimeUtils::Instance().GetTime() - lastTimeMovedInGrid < 2)
        AudioManager::Instance().PlayFx("hit.wav", 0.2);
}
