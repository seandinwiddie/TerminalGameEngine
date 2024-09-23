#include "Obstacle.h"
#include "AudioManager.h"
#include "TimeHelper.h"

Obstacle::Obstacle(int xPos, int yPos, Direction moveDir, float moveSpeed)
    : MovingStraightObject(xPos, yPos, moveDir, moveSpeed)
{
    SetModel(CreteModelUsingChar(219, 4, 2));
}

void Obstacle::OnCollisionEnter(GameObject* other, Direction collisionDirection)
{
    AudioManager::Instance().PlayFx("Platform/hit.wav", 0.2);
}
