#include "PressurePlate.h"
#include "AudioManager.h"

PressurePlate::PressurePlate(int xPos, int yPos) : GameObject(xPos, yPos)
{ 
    unpressedModel = CreteModelUsingChar('=',6,1);
    pressedModel = CreteModelUsingChar('_',6,1);
}

void PressurePlate::OnCollisionEnter(GameObject* other, Direction collisionDirection)
{
    if (collisionDirection == Direction::up)
    {
        OnPress.Notify();
        SetModel(pressedModel);
        AudioManager::Instance().PlayFx("Platform/buttonPress.wav");
    } 
}

void PressurePlate::OnCollisionExit(Direction collisionDirection)
{
    if (collisionDirection == Direction::up)
    {
        OnRelease.Notify();
        SetModel(unpressedModel);
        AudioManager::Instance().PlayFx("Platform/buttonRelease.wav");
    }
       
}