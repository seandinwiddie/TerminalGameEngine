#pragma once
#include "Collider.h"
#include "Bunny.h"
#include "AudioManager.h"

class PushableObject : public Collider
{
//---------------------------------------------------------- Fields
private:
    Model model = CreteModelUsingChar('@', 4, 2);
//---------------------------------------------------------- Methods
public:
    using Collider::Collider;
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 8; }
    virtual int GetColor() const { return Terminal::BLUE; }

protected:
    virtual void InitModel() override { SetModel(model); }
    virtual void OnCollisionEnter(Collider* other, Direction collisionDir)override
    {
        if (collisionDir == Direction::right || collisionDir == Direction::left)
        {
            TryMove(GetInverseDirection(collisionDir), 9999);
            collisions[collisionDir].clear();
        }
        else
        {
            if (dynamic_cast<Bunny*>(other) == nullptr)
                AudioManager::Instance().PlayFx("Resources/Sounds/Platform/Hit.wav", 0.2);
        }
    }
};