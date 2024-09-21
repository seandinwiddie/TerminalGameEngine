#pragma once

#include "Config.h"
#include "Level.h";
#include "Simulation.h";
#include "Obstacle.h";
#include "ObstaclesSpawner.h"

class CollisionsTestLevel : public Level
{
    //---------------------------------------------------------- Methods
public:
    virtual int GetWorldSizeX() const override { return 100; }
    virtual int GetWorldSizeY() const override { return 30; }
    virtual int GetScreenPadding() const override { return 4; }

    virtual void Load() override
    {
        Level::Load();

        Simulation& simulation = Simulation::Instance();
        simulation.Reset(this, GetWorldSizeX(), GetWorldSizeY(), GetScreenPadding(), false, {});

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
    }

    virtual double ShowGameOverScreenDelay()const { return 5; }
    virtual void OnGameOverDelayEnded() {}
};
