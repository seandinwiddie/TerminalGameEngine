#include "PlayerProjectile.h"
#include "Simulation.h"
#include "Enemy.h"
#include "SpaceInvadersLevel.h"

namespace SpaceInvaders
{
	const Model PlayerProjectile::MODEL(1, { '|' });

	void PlayerProjectile::OnCollisionEnter(Collider* other, Direction collisionDir)
	{
		Projectile::OnCollisionEnter(other, collisionDir);
		Enemy* otherEnemy = dynamic_cast<Enemy*>(other);
		if (otherEnemy != nullptr)
		{
			Engine::Simulation::Instance().RemoveEntity(otherEnemy);
		}
	}
}
