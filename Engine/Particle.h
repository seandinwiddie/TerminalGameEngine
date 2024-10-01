#pragma once
#include "ISimulationEntity.h"
#include "GridDirection.h"
#include "GameObject.h"
#include <vector>

template<typename T> using vector = std::vector<T>;
using Direction = GridDirection::Direction;

class Particle : public GameObject
{
private:
	vector<Direction> moveDirections;
	char modelChar;
	double moveSpeed;
	size_t remainingMovementsBeforeDestruction;
	
public:
	Particle(int xPos, int yPos, char modelChar, double moveSpeed, size_t movesBeforeDestruction);

protected:
	virtual void InitModel();
	virtual void Update();
	
private:
	void OnMoveCallback();
};