#include "PlayerProjectile.h"
#include "Simulation.h"
#include "Enemy.h"
#include "SpaceInvadersLevel.h"

const Model PlayerProjectile::MODEL = { {'|'} };

void PlayerProjectile::OnCollisionEnter(Collider* other, Direction collisionDir)
{
	Projectile::OnCollisionEnter(other, collisionDir);
	Enemy* otherEnemy = dynamic_cast<Enemy*>(other);
	if (otherEnemy != nullptr)
	{
		Simulation::Instance().RemoveEntity(otherEnemy);
	}
}