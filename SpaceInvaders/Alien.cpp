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
}

void Alien::Shot()
{
	EnemyProjectile* projectile = new EnemyProjectile(GetMidPosX(), GetPosY() -2 , Direction::down, PROJECTILE_SPEED);
	Simulation::Instance().TryAddEntity(projectile);
}