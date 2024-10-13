#include "CollisionsTestLevel.h"
#include "Config.h"
#include "Simulation.h"
#include "Obstacle.h"
#include "ObstaclesSpawner.h"

namespace Platformer
{
    template <typename T> using vector = std::vector<T>;

    void CollisionsTestLevel::LoadInSimulation()
    {
        Level::LoadInSimulation();
        Engine::Simulation& simulation = Engine::Simulation::Instance();

        //----------------------- spawners settings
        double spawnDelay = 0.15;
        double speed = 32;

        //----------------------- right spawner
        int xPosRight = 96;
        vector<int>ySpawnPoints = { 20,18,16,14 };
        ObstaclesSpawner* spawnerRight = new ObstaclesSpawner
        (
            xPosRight,
            spawnDelay,
            -speed,
            ySpawnPoints
        );
        simulation.TryAddEntity(spawnerRight);

        //----------------------- left spawner
        int xPosLeft = 2;
        vector<double>speeds2 = { 8, 1 };
        ObstaclesSpawner* spawnerLeft = new ObstaclesSpawner
        (
            xPosLeft,
            spawnDelay,
            speed,
            ySpawnPoints
        );
        simulation.TryAddEntity(spawnerLeft);
    }
}

