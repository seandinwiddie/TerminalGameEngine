#include "PressurePlate.h"
#include "AudioManager.h"

PressurePlate::PressurePlate(int xPos, int yPos) : GameObject(xPos, yPos)
{ 
    unpressedModel = CreteModelUsingChar('=',6,1);
    pressedModel = CreteModelUsingChar('_',6,1);
}

void PressurePlate::OnCollisionEnter(GameObject* other, Direction collisionDir)
{
    if (collisionDir == Direction::up && collisions[Direction::up].size() == 1)
    {
        OnPress.Notify();
        SetModel(pressedModel);
        AudioManager::Instance().PlayFx("Platform/buttonPress.wav");
    }
}

void PressurePlate::OnCollisionExit(Direction endingCollisionDir)
{
    if (endingCollisionDir == Direction::up && collisions[Direction::up].size() == 0)
    {
        OnRelease.Notify();
        SetModel(unpressedModel);
        AudioManager::Instance().PlayFx("Platform/buttonRelease.wav");
    }
       
}