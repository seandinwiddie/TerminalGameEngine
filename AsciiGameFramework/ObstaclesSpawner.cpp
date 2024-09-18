#include "ObstaclesSpawner.h"
#include "Obstacle.h"
#include "Simulation.h"
#include "TimeHelper.h"
#include "RandomUtils.h"

ObstaclesSpawner::ObstaclesSpawner
(
    int xPos,
    int yPos,
    const std::vector<float>& minSpawnDelays,
    const std::vector<float>& maxSpawnDelays,
    const std::vector<float>& speeds,
    float increaseIntensityEverySeconds,
    float stopSpawningWhenPhaseChangesDuration,
    const std::vector<int>& ySpawnPoints
) :
    TransformObject(xPos, yPos),
    minSpawnDelays(minSpawnDelays),
    maxSpawnDelays(maxSpawnDelays),
    speeds(speeds),
    increaseIntensityEverySeconds(increaseIntensityEverySeconds),
    stopSpawningWhenPhaseChangesDuration(stopSpawningWhenPhaseChangesDuration),
    ySpawnPoints(ySpawnPoints)
{
    assert(maxSpawnDelays.size() == speeds.size());
    spawnNextProjectileTime = GetNextSpawnObstacleTime();
    lastTimeIncreasedIntensity = TimeHelper::Instance().GetTime();
}

void ObstaclesSpawner::Update()
{
    double time = TimeHelper::Instance().GetTime();
    if (time >= spawnNextProjectileTime)
    {
        TryIncreaseIntensity(time);

        if (time - lastTimeIncreasedIntensity < stopSpawningWhenPhaseChangesDuration)
            return;

        spawnNextProjectileTime = GetNextSpawnObstacleTime();

        int randomPosY = ySpawnPoints[RandomUtils::GetRandomInt(0, ySpawnPoints.size() - 1)];
        Obstacle* obstacle = new Obstacle(GetPosX(), randomPosY, Direction::left, GetCurrentObstaclesSpeed());

        Simulation::Instance().TryAddGameObject(dynamic_cast<TransformObject*>(obstacle));
    }
}

void ObstaclesSpawner::TryIncreaseIntensity(float time)
{
    if (spawnIntensity < speeds.size() - 1 && (time - lastTimeIncreasedIntensity) > increaseIntensityEverySeconds + stopSpawningWhenPhaseChangesDuration)
    {
        ++spawnIntensity;
        lastTimeIncreasedIntensity = time;
    }
}

float ObstaclesSpawner::GetNextSpawnObstacleTime() const
{
    return TimeHelper::Instance().GetTime() +RandomUtils::GetRandomFloatBetween(GetCurrentMinSpawnDelay(), GetCurrentMaxSpawnDelay());
}