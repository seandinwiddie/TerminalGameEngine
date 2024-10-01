#include "Particle.h"
#include "RandomUtils.h"
#include "GridDirection.h"
#include "Simulation.h"

Particle::Particle
	(
		int xPos,
		int yPos, 
		char modelChar, 
		int color, double 
		moveSpeed, 
		size_t movesBeforeDestruction, 
		std::optional<Direction> mainDirection
	)
	: 
	GameObject(xPos, yPos),
	modelChar(modelChar), 
	color(color), 
	moveSpeed(moveSpeed), 
	remainingMovementsBeforeDestruction(movesBeforeDestruction)
{
	//--------- evaluate main direction

	
	if (!mainDirection.has_value()) //main direction = random value
	{
		moveDirections.push_back(static_cast<Direction>(RandomUtils::GetRandomInt(0, Direction::COUNT - 1)));
	}
	else //main direction is chosen randomly between given direction and orthogonal ones
	{
		int directionRandomness = RandomUtils::GetRandomInt(0, 2);

		if (directionRandomness == 0)
			moveDirections.push_back(mainDirection.value());
		else
		{
			moveDirections.push_back(GetClockwiseDirection(mainDirection.value()));
			if (directionRandomness == 2)
				moveDirections[0] = GetInverseDirection(moveDirections[0]);
		}
	}
		
	//--------- evaluate secondary direction 
	// 2/3 chanche to apply also a secondary direction, which may be one of the two possible orthogonals
	int directionRandomness = RandomUtils::GetRandomInt(0, 2);
	if (directionRandomness > 0)
	{
		Direction SecondaryDir = GridDirection::GetClockwiseDirection(moveDirections[0]);
		if (directionRandomness == 1)
			SecondaryDir = GetInverseDirection(SecondaryDir);
		moveDirections.push_back(SecondaryDir);

		//prevent particles with diagonal direction from disappearing earlier
		remainingMovementsBeforeDestruction *= 2;
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
		TryMove(dir, moveSpeed);
}

void Particle::OnMoveCallback()
{
	

	if (--remainingMovementsBeforeDestruction == 0)
		Simulation::Instance().RemoveEntity(this);
}