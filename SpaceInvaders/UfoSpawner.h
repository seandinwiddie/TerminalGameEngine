#pragma once
#include "ISimulationEntity.h"

class UfoSpawner : public ISimulationEntity
{
//---------------------------------------------------------- Settings
private:
	static const size_t MIN_SPAWN_DELAY = 15;
	static const size_t MAX_SPAWN_DELAY = 30;

//---------------------------------------------------------- Methods
protected:
	virtual void Update() = 0;
};