#pragma once

class ISimulationUpdatingEntity
{
	friend class Simulation;

protected:
	virtual void Update() = 0;
};