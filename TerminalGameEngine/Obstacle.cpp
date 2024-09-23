#include "Obstacle.h"
#include "AudioManager.h"
#include "TimeHelper.h"

Obstacle::Obstacle(int xPos, int yPos, Direction moveDir, double moveSpeed)
    : MovingStraightObject(xPos, yPos, moveDir, moveSpeed) { }

void Obstacle::OnCollisionEnter(GameObject* other, Direction collisionDirection)
{
    AudioManager::Instance().PlayFx("Platform/hit.wav", 0.2);
}
