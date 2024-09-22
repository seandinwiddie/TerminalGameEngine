#include "PressurePlate.h"
#include "AudioManager.h"

PressurePlate::PressurePlate(int xPos, int yPos) : CollidingObject(xPos, yPos)
{ 
    unpressedModel = CreteModelUsingChar('=',6,1);
    pressedModel = CreteModelUsingChar('_',6,1);
    SetModel(unpressedModel);
}

void PressurePlate::OnCollisionEnter(CollidingObject* other, Direction collisionDirection)
{
    if (collisionDirection == Direction::up)
    {
        OnPress.Notify();
        SetModel(pressedModel);
        AudioManager::Instance().PlayFx("buttonPress.wav");
    } 
}

void PressurePlate::OnCollisionExit(Direction collisionDirection)
{
    if (collisionDirection == Direction::up)
    {
        OnRelease.Notify();
        SetModel(unpressedModel);
        AudioManager::Instance().PlayFx("buttonRelease.wav");
    }
       
}