#include "PlayerProjectile.h"
#include "Simulation.h"
#include "Alien.h"
#include "SpaceInvadersLevel.h"

const Model PlayerProjectile::MODEL = { {'|'} };

void PlayerProjectile::OnCollisionEnter(GameObject* other, Direction collisionDir)
{
	SpaceInvadersLevel* level = dynamic_cast<SpaceInvadersLevel*>(Simulation::Instance().GetActiveLevel());
	assert(level != nullptr);

	Alien* otherAlien = dynamic_cast<Alien*>(other);
	if (otherAlien != nullptr)
	{
		level->IncreasePlayerScore(otherAlien->GetScore());
		Simulation::Instance().RemoveEntity(otherAlien);
	}

	Simulation::Instance().RemoveEntity(this);
}