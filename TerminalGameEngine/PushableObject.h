#pragma once
#include "GameObject.h"
#include "Bunny.h"
#include "AudioManager.h"

class PushableObject : public GameObject
{
private:
    Model model = CreteModelUsingChar('@', 4, 2);
//---------------------------------------------------------- Methods
public:
    PushableObject(int xPos, int yPos) :GameObject(xPos, yPos){}
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 8; }
    virtual int GetColor() const { return Terminal::BLUE; }

protected:
    virtual void OnCollisionExit(Direction endingCollisionDir) override {}
    virtual void InitModel() override { SetModel(model); }
    virtual void OnCollisionEnter(uset<GameObject*>collidingObjects, Direction collisionDir)override
    {
        if (collisionDir == Direction::right || collisionDir == Direction::left)
        {
            Move(GetInverseDirection(collisionDir), 9999);
            collidingDirections[collisionDir] = false;
        }
        else
        {
            for (GameObject* collider : collidingObjects)
            {
                if (dynamic_cast<Bunny*>(collider) == nullptr)
                    AudioManager::Instance().PlayFx("Platform/hit.wav", 0.2);
            }
        }
    }
};