#include "ObstaclesSpawner.h"
#include "Obstacle.h"
#include "Simulation.h"
#include "TimeHelper.h"
#include "RandomUtils.h"
#include <cstdlib>

ObstaclesSpawner::ObstaclesSpawner
(
    int xPos,
    const std::vector<float>& minSpawnDelays,
    const std::vector<float>& maxSpawnDelays,
    const std::vector<float>& speeds,
    const std::vector<int>& ySpawnPoints,
    float increaseIntensityEverySeconds,
    float stopSpawningWhenPhaseChangesDuration
) :
    xPos(xPos),
    minSpawnDelays(minSpawnDelays),
    maxSpawnDelays(maxSpawnDelays),
    speeds(speeds),
    increaseIntensityEverySeconds(increaseIntensityEverySeconds),
    stopSpawningWhenPhaseChangesDuration(stopSpawningWhenPhaseChangesDuration),
    ySpawnPoints(ySpawnPoints)
{
    assert(maxSpawnDelays.size() == speeds.size() && minSpawnDelays.size() == speeds.size());
    spawnNextProjectileTime = GetNextSpawnObstacleTime();
    lastTimeIncreasedIntensity = TimeHelper::Instance().GetTime();
}

ObstaclesSpawner::ObstaclesSpawner
(
    int xPos,
    float spawnDelay,
    float speed,
    const std::vector<int>& ySpawnPoints
) :
    ObstaclesSpawner(
        xPos,
        std::vector<float>{spawnDelay},
        std::vector<float>{spawnDelay},
        std::vector<float>{speed},
        ySpawnPoints
    )
{ }

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

        float obstacleSpeed = GetCurrentObstaclesSpeed();
        Direction direction = obstacleSpeed > 0 ? Direction::right : Direction::left;
        obstacleSpeed = abs(obstacleSpeed);
        Obstacle* obstacle = new Obstacle(xPos, randomPosY, direction, obstacleSpeed);

        Simulation::Instance().TryAddObject(dynamic_cast<GameObject*>(obstacle));
    }
}

void ObstaclesSpawner::TryIncreaseIntensity(float time)
{
    if (increaseIntensityEverySeconds == -1)
        return;

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