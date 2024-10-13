#include "ShieldPart.h"
#include "Simulation.h"
#include "Alien.h"
#include "Projectile.h"
#include "AudioManager.h"

namespace SpaceInvaders
{
    void ShieldPart::OnCollisionEnter(Collider* other, Direction collisionDir)
    {
        Collider::OnCollisionEnter(other, collisionDir);

        Projectile* otherProjectile = dynamic_cast<Projectile*>(other);
        if (otherProjectile != nullptr)
        {
            Engine::AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/ShieldBreak.wav");
            Engine::Simulation::Instance().RemoveEntity(this);
            return;
        }

        Alien* otherAlien = dynamic_cast<Alien*>(other);
        if (otherAlien != nullptr)
        {
            Engine::Simulation::Instance().RemoveEntity(this);
            return;
        }
    }
}