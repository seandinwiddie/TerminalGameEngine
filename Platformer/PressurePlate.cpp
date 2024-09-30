#include "PressurePlate.h"
#include "AudioManager.h"

PressurePlate::PressurePlate(int xPos, int yPos, size_t width) : GameObject(xPos, yPos)
{ 
    unpressedModel = CreteModelUsingChar('=', width, 1);
    pressedModel = CreteModelUsingChar('_', width, 1);
}

void PressurePlate::OnCollisionEnter(GameObject* other, Direction collisionDir)
{
    if (collisionDir == Direction::up && collisions[Direction::up].size() == 1)
    {
        OnPress.Notify();
        SetModel(pressedModel);
        AudioManager::Instance().PlayFx("Resources/Sounds/Platform/ButtonPress.wav");
    }
}

void PressurePlate::OnCollisionExit(Direction endingCollisionDir)
{
    if (endingCollisionDir == Direction::up && collisions[Direction::up].size() == 0)
    {
        OnRelease.Notify();
        SetModel(unpressedModel);
        AudioManager::Instance().PlayFx("Resources/Sounds/Platform/ButtonRelease.wav");
    }
       
}