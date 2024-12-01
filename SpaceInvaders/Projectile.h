#pragma once
#include "MovingStraightObject.h"
#include "Simulation.h"
#include "Enemy.h"
#include "ShieldPart.h"

namespace SpaceInvaders
{
    template<typename T> using shared_ptr = std::shared_ptr<T>;
    using Direction = Engine::Direction;

    class Projectile : public Engine::MovingStraightObject
    {
        //---------------------------------------------------------- Methods
    public:
        using MovingStraightObject::MovingStraightObject;

    protected:
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        virtual void OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir)
        {
            MovingStraightObject::OnCollisionEnter(other, collisionDir);
            Direction collisionOppositeDirection = DirectionUtils::GetInverseDirection(collisionDir);

            shared_ptr<Enemy> otherEnemy = std::dynamic_pointer_cast<Enemy>(other);
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
                    8,     //speed
                    3,      //movement life
                    4,      //density
                    collisionOppositeDirection
                );
            }

            Engine::Simulation::Instance().RemoveEntity(shared_from_this());
        }
    };
}