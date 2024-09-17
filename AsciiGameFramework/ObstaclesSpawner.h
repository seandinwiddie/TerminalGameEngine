#pragma once
#include "TransformObject.h"

class ObstaclesSpawner : public TransformObject
{
//---------------------------------------------------------- Fields
private:
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
        const int xPos,
        const int yPos,
        const std::vector<float>& minSpawnDelays,
        const std::vector<float>& maxSpawnDelays,
        const std::vector<float>& speeds,
        const float increaseIntensityEverySeconds,
        const float stopSpawningWhenPhaseChangesDuration,
        const std::vector<int>& ySpawnPoints
    );

    void Update() override;
    virtual bool CanExitScreenSpace() const override { return true; }
    virtual float GetGravityScale() const override { return 0; }

private:
    float GetCurrentMinSpawnDelay() const { return minSpawnDelays[spawnIntensity]; }
    float GetCurrentMaxSpawnDelay() const { return maxSpawnDelays[spawnIntensity]; }
    float GetCurrentObstaclesSpeed() const { return speeds[spawnIntensity]; }
    float GetNextSpawnObstacleTime() const;
    void TryIncreaseIntensity(const float time);
};