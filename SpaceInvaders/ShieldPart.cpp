#include "ShieldPart.h"
#include "Simulation.h"
#include "Alien.h"
#include "Projectile.h"
#include "AudioManager.h"

void ShieldPart::OnCollisionEnter(GameObject* other, Direction collisionDir)
{
    GameObject::OnCollisionEnter(other, collisionDir);

    Projectile* otherProjectile = dynamic_cast<Projectile*>(other);
    if (otherProjectile != nullptr)
    {
        AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/ShieldBreak.wav");
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