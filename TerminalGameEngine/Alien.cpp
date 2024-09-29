#include "Alien.h"
#include "TimeHelper.h"
#include "AudioManager.h"
#include "EnemyProjectile.h"
#include "Simulation.h"

void Alien::Update()
{
	bool showFirstAnimFrameNew = TimeHelper::Instance().IsTimeForFirstOfTwoModels(1);
	if (isFirsAnimationFrameTime != showFirstAnimFrameNew)
	{
		StepAnimation();
		isFirsAnimationFrameTime = showFirstAnimFrameNew;
	}
}

void Alien::CALLED_BY_SIM_OnDestroy()
{
	AudioManager::Instance().PlayFx("SpaceInv/alienDeath2.wav");
	OnDestroy.Notify(this);
}

void Alien::Shot()
{
	EnemyProjectile* projectile = new EnemyProjectile(GetMidPosX(), GetPosY() -2 , Direction::down, PROJECTILE_SPEED);
	Simulation::Instance().TryAddEntity(projectile);
	//AudioManager::Instance().PlayFx("SpaceInv/shot1.wav");
}