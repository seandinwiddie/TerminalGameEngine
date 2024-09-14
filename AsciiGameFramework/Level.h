#pragma once

#include "Config.h"
#include "Simulation.h"
#include "Bunny.h"
#include "StaticCollider.h"
#include "LevelEndFlag.h"
#include "AutomaticDoor.h"
#include "PressurePlate.h"
#include "ObstaclesSpawner.h"
#include "PushableObject.h"

class Level : public SimulationObject
{
protected:
    double gameOverTime = -1;
    double levelStartedTime;

public:
	virtual void Load() = 0;
	virtual void OnGameOver() = 0;
    double GetLevelTime() const;
    bool IsGameOver() const { return gameOverTime > -1; }

protected:
    virtual void Update()override {}
};