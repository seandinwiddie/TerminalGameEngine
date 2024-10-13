#pragma once
#include "StaticCollider.h"

namespace SpaceInvaders
{
    using Direction = Engine::Direction;
    using Model = Engine::Model;

    class ShieldPart : public Engine::Collider
    {
        //---------------------------------------------------------- Fields
    private:
        Model model = CreteModelUsingChar('=', 1, 1);

        //---------------------------------------------------------- Methods
    public:
        using Collider::Collider;

    protected:
        virtual bool CanExitScreenSpace() const override { return false; }
        virtual double GetGravityScale() const override { return 0; }
        virtual int GetColor() const { return Engine::Terminal::GREEN; }
        virtual void InitModel() { SetModel(model); }
        virtual void OnCollisionEnter(Collider* other, Direction collisionDir);
    };
}