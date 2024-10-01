#pragma once
#include "Config.h"
#include "GridDirection.h"
#include "ISimulationEntity.h"
#include "Terminal.h"
#include "Event.h"

#include <Windows.h>
#include <vector>



template<typename T> using vector = std::vector<T>;
using namespace GridDirection;
using Model = std::vector<std::vector<char>>;

class KinematicObject : public ISimulationEntity
{
	friend class Simulation;

//---------------------------------------------------------- Fields
public:
	Event<GameObject*, Direction> OnMove;
	// generic on destroy event could be added

protected:
	bool canMove = true;

private:
	int xPos;
	int yPos;

	double xPosContinuous;
	double yPosContinuous;

	bool mustBeReprinted = true;
	const Model* model = nullptr;

//---------------------------------------------------------- Methods
};