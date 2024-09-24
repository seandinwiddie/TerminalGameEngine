#pragma once
#include "GameObject.h"
#include "Bunny.h"
#include "AudioManager.h"

class PushableObject : public GameObject
{
//---------------------------------------------------------- Methods
public:
    PushableObject(int xPos, int yPos) :GameObject(xPos, yPos){}
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 8; }
    virtual int GetColor() const { return Terminal::BLUE; }

protected:
    virtual void OnCollisionExit(Direction endingCollisionDir) override {}
    virtual void InitModel() override { SetModel(CreteModelUsingChar('@', 4, 2)); }
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDir)override
    {
        if (collisionDir == Direction::right || collisionDir == Direction::left)
        {
            Move(GetInverseDirection(collisionDir), 9999);
            collidingDirections[static_cast<int>(collisionDir)] = false;
        }
        else if (dynamic_cast<Bunny*>(other) == nullptr)
        {
            AudioManager::Instance().PlayFx("Platform/hit.wav", 0.2);
        }
    }
};