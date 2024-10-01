#include "Alien.h"
#include "TimeHelper.h"
#include "AudioManager.h"
#include "EnemyProjectile.h"
#include "Simulation.h"

void Alien::OnDestroy()
{
	Enemy::OnDestroy();
	AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/AlienDeath2.wav");
	OnDestroyEvent.Notify(this);
	Simulation::Instance().SpawnParticles(GetPosX(), GetPosY(), GetModelWidth(), GetModelHeight(), '*', GetColor(),8,4, 1.0);
}

void Alien::Shot()
{
	EnemyProjectile* projectile = new EnemyProjectile(GetMidPosX(), GetPosY() -2 , Direction::down, PROJECTILE_SPEED);
	Simulation::Instance().TryAddEntity(projectile);
}

void Alien::Update()
{
	bool showFirstAnimFrameNew = TimeHelper::Instance().IsTimeForFirstOfTwoModels(1);
	if (isFirsAnimationFrameTime != showFirstAnimFrameNew)
	{
		StepAnimation();
		isFirsAnimationFrameTime = showFirstAnimFrameNew;
	}
}