#pragma once
#include "ISimulationEntity.h"
#include "GridDirection.h"
#include "ParticleGroup.h"
#include <vector>

template<typename T> using vector = std::vector<T>;
using Direction = GridDirection::Direction;

class Particle
{
private:
	int posX;
	int posY;
	char model;
	vector<Direction> directions;
	

public:
	Particle(int posX, int posY, char model, vector<Direction> directions) :
		posX(posX), posY(posY), model(model), directions(directions){ }
};