#pragma once
#include "MovingStraightObject.h"
#include "Simulation.h"

class Projectile : public MovingStraightObject
{
//---------------------------------------------------------- Methods
public:
    using MovingStraightObject::MovingStraightObject;

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
    virtual void OnCollisionEnter(Collider* other, Direction collisionDir)
    {
        MovingStraightObject::OnCollisionEnter(other, collisionDir);
        Simulation::Instance().RemoveEntity(this);
    }
};

