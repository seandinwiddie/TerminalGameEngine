#include "UfoSpawner.h"
#include "TimeHelper.h"
#include "Ufo.h"
#include "Simulation.h"
#include "RandomUtils.h"

UfoSpawner::UfoSpawner(int xSpawnPos, int ySpawnPos, Direction ufoMoveDirection)
	: xSpawnPos(xSpawnPos), ySpawnPos(ySpawnPos), ufoMoveDirection(ufoMoveDirection)
{
	SetNextSpawnDelay();
}

void UfoSpawner::Update()
{
	if(TimeHelper::Instance().GetTime() - lastTimeSpawned > nextSpawnDelay)
	{
		Ufo* ufo = new Ufo(xSpawnPos,ySpawnPos,ufoMoveDirection);
		Simulation::Instance().TryAddEntity(ufo);
		lastTimeSpawned = TimeHelper::Instance().GetTime();
		SetNextSpawnDelay();
	}
}

void UfoSpawner::SetNextSpawnDelay()
{
	nextSpawnDelay =
		TimeHelper::Instance().GetTime() +
		RandomUtils::GetRandomDoubleBetween(MIN_SPAWN_DELAY, MAX_SPAWN_DELAY);
}