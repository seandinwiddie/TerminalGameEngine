#pragma once
#include "GameObject.h"

class ObstaclesSpawner : public ISimulationUpdatingEntity
{
//---------------------------------------------------------- Fields
private:
    int xPos;
    std::vector<float> minSpawnDelays;
    std::vector<float> maxSpawnDelays;
    std::vector<float> speeds;
    std::vector<int> ySpawnPoints;
    uint spawnIntensity = 0;
    float stopSpawningWhenPhaseChangesDuration;
    float increaseIntensityEverySeconds;
    double spawnNextProjectileTime;
    double lastTimeIncreasedIntensity = 0;

//---------------------------------------------------------- Methods
public:

    ObstaclesSpawner
    (
        int xPos,
        const std::vector<float>& minSpawnDelays,
        const std::vector<float>& maxSpawnDelays,
        const std::vector<float>& speeds,
        const std::vector<int>& ySpawnPoints,
        float increaseIntensityEverySeconds = -1,
        float stopSpawningWhenPhaseChangesDuration = 0
    );

    ObstaclesSpawner
    (
        int xPos,
        float spawnDelay,
        float speed,
        const std::vector<int>& ySpawnPoints
    );

protected:
    void Update() override;

private:
    float GetCurrentMinSpawnDelay() const { return minSpawnDelays[spawnIntensity]; }
    float GetCurrentMaxSpawnDelay() const { return maxSpawnDelays[spawnIntensity]; }
    float GetCurrentObstaclesSpeed() const { return speeds[spawnIntensity]; }
    float GetNextSpawnObstacleTime() const;
    void TryIncreaseIntensity(float time);
};