#include "Enemy.h"
#include "TimeHelper.h"
#include "Simulation.h"
#include "SpaceInvadersLevel.h"

void Enemy::OnDestroy()
{
	SpaceInvadersLevel* level = dynamic_cast<SpaceInvadersLevel*>(Simulation::Instance().GetActiveLevel());
	assert(level != nullptr);
	level->IncreasePlayerScore(GetScore());
	Simulation::Instance().SpawnParticles
	(
		GetPosX(), 
		GetPosY(),
		GetModelWidth(),
		GetModelHeight(), 
		'*',
		GetColor(),
		16,	//speed
		4,	//lifetime
		1	//density
	);
}