#pragma once
#include "Collider.h"
#include "Bunny.h"
#include "AudioManager.h"

namespace Platformer
{
    class PushableObject : public Engine::Collider
    {
        //---------------------------------------------------------- Fields
    private:
        Model model = CreteModelUsingChar('@', 4, 2);
        //---------------------------------------------------------- Methods
    public:
        using Collider::Collider;
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 8; }
        virtual int GetColor() const { return Engine::Terminal::BLUE; }

    protected:
        void InitModel() override { SetModel(model); }
        void OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir)override
        {
            if (collisionDir == Direction::right || collisionDir == Direction::left)
            {
                TryMove(DirectionUtils::GetInverseDirection(collisionDir), 9999);
                collisions[collisionDir].clear();
            }
            else
            {
                if(std::dynamic_pointer_cast<Bunny>(other))
                   Engine::AudioManager::Instance().PlayFx("Resources/Sounds/Platform/Hit.wav", 0.2);
            }
        }
    };
}