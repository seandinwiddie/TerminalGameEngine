#pragma once

class ISimulationUpdatingEntity
{
friend class Simulation;
//---------------------------------------------------------- Methods
protected:
	virtual void Update() = 0;
};