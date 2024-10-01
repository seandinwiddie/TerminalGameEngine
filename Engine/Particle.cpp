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
		
	//--------- evaluate orthogonal direction
	
	Direction orthogonalDirection = GetClockwiseDirection(moveDirections[0]);
	if (RandomUtils::GetRandomBool())
		orthogonalDirection = GetInverseDirection(orthogonalDirection);
	moveDirections.push_back(orthogonalDirection);

	//--------- evaluate directions speeds

	double orthogonalSpeed = RandomUtils::GetRandomDouble(0, moveSpeed);
	moveSpeed -= orthogonalSpeed;
	
	moveSpeeds.push_back(moveSpeed);
	moveSpeeds.push_back(orthogonalSpeed);

	OnMove.Subscribe([this](GameObject* _, Direction __) { OnMoveCallback(); });
}

void Particle::InitModel()
{
	model = CreteModelUsingChar(modelChar, 1, 1);
	SetModel(model);
}

void Particle::Update()
{
	for(int i = 0; i < moveDirections.size(); ++i)
		TryMove(moveDirections[i], moveSpeeds[i]);		
}

void Particle::OnMoveCallback()
{
	if (--remainingMovementsBeforeDestruction == 0)
		Simulation::Instance().RemoveEntity(this);
}