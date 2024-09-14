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
#include "Simulation.h"

class ILevel
{
public:
	virtual void Load() = 0;
	virtual void OnGameOver() = 0;
};