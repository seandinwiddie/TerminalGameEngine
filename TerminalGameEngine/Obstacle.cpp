#include "Obstacle.h"
#include "AudioManager.h"
#include "TimeHelper.h"

Obstacle::Obstacle(int xPos, int yPos, Direction moveDir, float moveSpeed)
    : MovingStraightObject(xPos, yPos, moveDir, moveSpeed)
{
    SetModel(CreteModelUsingChar(219, 4, 2));
}

void Obstacle::OnCollisionEnter(CollidingObject* other, Direction collisionDirection)
{
    AudioManager::Instance().PlayFx("hit.wav", 0.2);
}
