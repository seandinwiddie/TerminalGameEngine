#pragma once

#include "MovingStraightObject.h"

namespace Platformer
{
    using Model = Engine::Model;
    using Direction = Engine::Direction;

    class Obstacle : public Engine::MovingStraightObject
    {
    private:
        static Model model;
        //---------------------------------------------------------- Methods
    public:
        using MovingStraightObject::MovingStraightObject;

        virtual bool CanExitScreenSpace() const override { return true; }
        virtual double GetGravityScale() const override { return 0; }
        virtual int GetColor() const { return Engine::Terminal::RED; }

    protected:
        virtual void OnCollisionEnter(Collider* other, Direction collisionDir) override;
        virtual void InitModel();
    };
}