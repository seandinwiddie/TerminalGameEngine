#pragma once
#include "MovingStraightObject.h"
#include "Simulation.h"
#include "Enemy.h"
#include "ShieldPart.h"

namespace SpaceInvaders
{
    using Direction = Engine::Direction;

    class Projectile : public Engine::MovingStraightObject
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

            Enemy* otherEnemy = dynamic_cast<Enemy*>(other);

            if (otherEnemy == nullptr)
            {
                Engine::Simulation::Instance().SpawnParticles
                (
                    GetPosX(),
                    GetPosY(),
                    GetModelWidth(),
                    GetModelHeight(),
                    '*',
                    GetColor(),
                    12,     //speed
                    3,      //movement life
                    4,      //density
                    collisionOppositeDirection
                );
            }

            Engine::Simulation::Instance().RemoveEntity(this);
        }
    };
}