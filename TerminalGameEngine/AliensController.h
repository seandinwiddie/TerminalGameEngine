#pragma once
#include "ISimulationEntity.h"
#include "GridDirection.h"
#include <vector>

class Alien;
template <typename T> using vector = std::vector<T>;
using namespace GridDirection;

class AliensController : public ISimulationEntity
{
//------------------------------------------------------------------- Settings

//------------------------------------------------------------------- Fields
private:
	vector<vector<Alien*>> aliens;

	size_t aliensCount;

	size_t aliensCountX;
	size_t aliensCountY;

	Direction currentDirection = Direction::right;

//------------------------------------------------------------------- Methods
public:
	AliensController(int aliensCountX, int aliensCountY);
	void Update() override;
	void RegisterAlien(Alien* alien, int xPos, int yPos);

private:
	double GetCurrentSpeedX(){ return 8; }
};