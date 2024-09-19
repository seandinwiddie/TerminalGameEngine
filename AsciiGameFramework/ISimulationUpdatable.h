#pragma once

class ISimulationUpdatable
{
	friend class Simulation;

protected:
	virtual void Update() = 0;
};