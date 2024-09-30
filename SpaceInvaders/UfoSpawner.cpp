#include "UfoSpawner.h"
#include "TimeHelper.h"
#include "Ufo.h"
#include "Simulation.h"
#include "RandomUtils.h"
#include "DebugManager.h"

UfoSpawner::UfoSpawner(int xSpawnPos, int ySpawnPos, Direction ufoMoveDirection)
	: xSpawnPos(xSpawnPos), ySpawnPos(ySpawnPos), ufoMoveDirection(ufoMoveDirection)
{
	SetNextSpawnDelay();
}

void UfoSpawner::Update()
{
	if(TimeHelper::Instance().GetTime() >  nextSpawnTime)
	{
		Ufo* ufo = new Ufo(xSpawnPos,ySpawnPos,ufoMoveDirection);
		Simulation::Instance().TryAddEntity(ufo);
		lastTimeSpawned = TimeHelper::Instance().GetTime();
		SetNextSpawnDelay();
	}
	DebugManager::Instance().PrintGenericLog(std::to_string(TimeHelper::Instance().GetTime()),5);
	DebugManager::Instance().PrintGenericLog(std::to_string(nextSpawnTime), 6);
}

void UfoSpawner::SetNextSpawnDelay()
{
	nextSpawnTime =
		TimeHelper::Instance().GetTime() +
		RandomUtils::GetRandomDoubleBetween(MIN_SPAWN_DELAY, MAX_SPAWN_DELAY);
}