#include "EnemyProjectile.h"
#include "PlayerTank.h"

const Model EnemyProjectile::MODEL(1, { '|' });

void EnemyProjectile::OnCollisionEnter(Collider* other, Direction collisionDir)
{
	Projectile::OnCollisionEnter(other, collisionDir);
	
	PlayerTank* otherTank = dynamic_cast<PlayerTank*>(other);
	if (otherTank != nullptr)
		otherTank->TakeDamage();
}