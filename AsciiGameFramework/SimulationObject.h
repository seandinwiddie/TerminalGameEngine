#pragma once

class SimulationObject
{
	friend class Simulation;

protected:
	virtual void Update() = 0;
};