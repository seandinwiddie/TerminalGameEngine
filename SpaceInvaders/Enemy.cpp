#include "Enemy.h"
#include "TimeHelper.h"
#include "Simulation.h"
#include "SpaceInvadersLevel.h"

namespace SpaceInvaders
{
	void Enemy::OnDestroy()
	{
		SpaceInvadersLevel* level = dynamic_cast<SpaceInvadersLevel*>(Engine::Simulation::Instance().GetActiveLevel());
		assert(level != nullptr);
		level->IncreasePlayerScore(GetScore());
		Engine::Simulation::Instance().SpawnParticles
		(
			GetPosX(),
			GetPosY(),
			GetModelWidth(),
			GetModelHeight(),
			'*',
			Engine::Terminal::RED,
			0.1,	//speed
			100,//lifetime
			10	//density
		);
	}
}