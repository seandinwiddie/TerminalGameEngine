#include "PressurePlate.h"
#include "AudioManager.h"

PressurePlate::PressurePlate(int xPos, int yPos) : GameObject(xPos, yPos)
{ 
    unpressedModel = CreteModelUsingChar('=',6,1);
    pressedModel = CreteModelUsingChar('_',6,1);
}

void PressurePlate::OnCollisionEnter(uset<GameObject*>collidingObjects, Direction collisionDir)
{
    if (collisionDir == Direction::up)
    {
        OnPress.Notify();
        SetModel(pressedModel);
        AudioManager::Instance().PlayFx("Platform/buttonPress.wav");
    } 
}

void PressurePlate::OnCollisionExit(Direction endingCollisionDir)
{
    if (endingCollisionDir == Direction::up)
    {
        OnRelease.Notify();
        SetModel(unpressedModel);
        AudioManager::Instance().PlayFx("Platform/buttonRelease.wav");
    }
       
}