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
        Direction collisionOppositeDirection = GetInverseDirection(collisionDir);
        
        Projectile* otherProjectile = dynamic_cast<Projectile*>(other);
        if (otherProjectile != nullptr || other == WorldSpace::SCREEN_MARGIN)
        {
            Simulation::Instance().SpawnParticles
            (
                GetPosX(),
                GetPosY(),
                GetModelWidth(),
                GetModelHeight(),
                '*', GetColor(),
                12,     //speed
                4,      //movement life
                5,      //density
                collisionOppositeDirection
            );
        }
        Simulation::Instance().RemoveEntity(this);
    }
};

