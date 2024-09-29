#pragma once

class ISimulationEntity
{
friend class Simulation;
//---------------------------------------------------------- Methods
protected:
	virtual void Update() = 0;
};