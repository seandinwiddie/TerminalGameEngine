// This is a debug level
#pragma once

#include "Config.h"
#include "Level.h";
#include "Simulation.h";
#include "Obstacle.h";

class RepeatedCollisionTestLevel : public Level
{
//---------------------------------------------------------- Settings
private:
    static const uint WORLD_SIZE_X = 120;
    static const uint WORLD_SIZE_Y = 30;
    static const uint SCREEN_PADDING = 4;

//---------------------------------------------------------- Methods
public:
    virtual void Load() override
    {
        Level::Load();

        Simulation& simulation = Simulation::Instance();
        simulation.Reset(this, WORLD_SIZE_X, WORLD_SIZE_Y, SCREEN_PADDING, true, {});

        Obstacle* obstacleSlow = new Obstacle(90,5, Direction::left, 1);
        Simulation::Instance().TryAddGameObject(dynamic_cast<TransformObject*>(obstacleSlow));

        Obstacle* obstacleFast = new Obstacle(95, 5, Direction::left, 8);
        Simulation::Instance().TryAddGameObject(dynamic_cast<TransformObject*>(obstacleFast));
    }

    virtual double ShowGameOverScreenDelay()const { return 5; }
    virtual void OnGameOverDelayEnded() {}
};