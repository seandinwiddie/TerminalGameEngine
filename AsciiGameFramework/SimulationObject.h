#pragma once

class SimulationObject
{
	friend class Simulation;

protected:
	//todo make private in subclasses
	virtual void Update() = 0;
};