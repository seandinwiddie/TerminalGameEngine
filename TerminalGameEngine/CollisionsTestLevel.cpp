#include "CollisionsTestLevel.h"
#include "Config.h"
#include "Simulation.h";
#include "Obstacle.h";
#include "ObstaclesSpawner.h"

void CollisionsTestLevel::Load()
{
    Level::Load();

    Simulation& simulation = Simulation::Instance();
    simulation.Reset(this, GetWorldSizeX(), GetWorldSizeY(), GetScreenPadding(), false, {});

    float spawnDelay = 0.15;
    float speed = 4;

    vector<int>ySpawnPoints = { 20,18,16,14 };
    ObstaclesSpawner* spawnerRight = new ObstaclesSpawner
    (
        96,
        spawnDelay,
        -speed,
        ySpawnPoints
    );
    simulation.AddUpdatable(spawnerRight);


    vector<float>speeds2 = { 8, 1 };
    ObstaclesSpawner* spawnerLeft = new ObstaclesSpawner
    (
        2,
        spawnDelay,
        speed,
        ySpawnPoints
    );
    simulation.AddUpdatable(spawnerLeft);
}