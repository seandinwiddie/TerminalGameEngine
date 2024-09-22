#include "CollisionsTestLevel.h"
#include "Config.h"
#include "Simulation.h";
#include "Obstacle.h";
#include "ObstaclesSpawner.h"

void CollisionsTestLevel::LoadInSimulation()
{
    Level::LoadInSimulation();
    Simulation& simulation = Simulation::Instance();

    float spawnDelay = 0.15;
    float speed = 32;

    vector<int>ySpawnPoints = { 20,18,16,14 };
    ObstaclesSpawner* spawnerRight = new ObstaclesSpawner
    (
        96,
        spawnDelay,
        -speed,
        ySpawnPoints
    );
    simulation.TryAddEntity(spawnerRight);


    vector<float>speeds2 = { 8, 1 };
    ObstaclesSpawner* spawnerLeft = new ObstaclesSpawner
    (
        2,
        spawnDelay,
        speed,
        ySpawnPoints
    );
    simulation.TryAddEntity(spawnerLeft);
}