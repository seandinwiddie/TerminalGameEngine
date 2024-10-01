#include "Particle.h"
#include "RandomUtils.h"
#include "GridDirection.h"
#include "Simulation.h"

Particle::Particle(int xPos, int yPos, char modelChar, int color, double moveSpeed, size_t movesBeforeDestruction) 
	: GameObject(xPos, yPos), modelChar(modelChar), color(color), moveSpeed(moveSpeed), remainingMovementsBeforeDestruction(movesBeforeDestruction)
{
	Direction randomDir = static_cast<Direction>(RandomUtils::GetRandomInt(0, Direction::COUNT - 1));
	moveDirections.push_back(randomDir);
	if (RandomUtils::GetRandomBool())
	{
		Direction SecondaryDir = GridDirection::GetClockwiseDirection(randomDir);
		if (RandomUtils::GetRandomBool())
			SecondaryDir = GetInverseDirection(SecondaryDir);
		moveDirections.push_back(SecondaryDir);
	}

	OnMove.Subscribe([this](GameObject* _, Direction __) { OnMoveCallback(); });
}

void Particle::InitModel()
{
	model = CreteModelUsingChar(modelChar, 1, 1);
	SetModel(model);
}

void Particle::Update()
{
	for (Direction dir : moveDirections)
		TryMove(dir, 8);
}

void Particle::OnMoveCallback()
{
	if (--remainingMovementsBeforeDestruction == 0)
		Simulation::Instance().RemoveEntity(this);
}