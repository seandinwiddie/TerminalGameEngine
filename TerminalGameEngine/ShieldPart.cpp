#include "ShieldPart.h"
#include "Simulation.h"
#include "Alien.h"
#include "Projectile.h"

void ShieldPart::OnCollisionEnter(GameObject* other, Direction collisionDir)
{
    GameObject::OnCollisionEnter(other, collisionDir);

    Projectile* otherProjectile = dynamic_cast<Projectile*>(other);
    if (otherProjectile != nullptr)
    {
        Simulation::Instance().RemoveEntity(this);
        return;
    }

    Alien* otherAlien = dynamic_cast<Alien*>(other);
    if (otherAlien != nullptr)
    {
        Simulation::Instance().RemoveEntity(this);
        return;
    }
}