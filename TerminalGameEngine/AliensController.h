#pragma once
#include "ISimulationEntity.h"
#include <vector>

template <typename T> using vector = std::vector<T>;

class AliensController : ISimulationEntity
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
	AliensController(int aliensCountX, int aliensCountY) : aliensCountX(aliensCountX), aliensCountY(aliensCountY)
	{
		aliensCount = aliensCountX * aliensCountY;

		aliens.resize(aliensCountY);
		for (int i = 0; i < aliensCountX; ++i)
			aliens[i].resize(aliensCountX);
	}

	void Update() override
	{
		for (int y = 0; y < aliensCountY; ++y)
			for (int x = 0; x < aliensCountX; ++x)
				aliens[y][x]->TryMove(currentDirection, GetCurrentSpeedX());
	}

private:
	double GetCurrentSpeedX()
	{
		return 8;
	}
};