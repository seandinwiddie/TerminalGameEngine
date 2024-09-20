#pragma once

#include "Config.h"
#include "Level.h";
#include "Simulation.h";
#include "Obstacle.h";
#include "ObstaclesSpawner.h"

class CollisionsTestLevel : public Level
{
    //---------------------------------------------------------- Settings
private:
    static const uint WORLD_SIZE_X = 100;
    static const uint WORLD_SIZE_Y = 30;
    static const uint SCREEN_PADDING = 4;

    //---------------------------------------------------------- Methods
public:
    virtual void Load() override
    {
        Level::Load();

        Simulation& simulation = Simulation::Instance();
        simulation.Reset(this, WORLD_SIZE_X, WORLD_SIZE_Y, SCREEN_PADDING, false, {});

        //---
        float spawnDelay = 0.15;
        float speed = 4;
        
        vector<int>ySpawnPoints = {20,18,16,14 };
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
        //---
        
        //Obstacle* obstacle = new Obstacle(90, 10, Direction::left, 8);
        //simulation.TryAddObject(obstacle);
    }

    virtual double ShowGameOverScreenDelay()const { return 5; }
    virtual void OnGameOverDelayEnded() {}
};
