#include "KinematicObject.h"
#include "TimeHelper.h"
#include "Simulation.h"

KinematicObject::KinematicObject(int xPos, int yPos) :
	xPos(xPos),
	yPos(yPos),
	xPosContinuous(xPos),
	yPosContinuous(yPos)
{
	ResetPartialMovement();
}

size_t KinematicObject::GetModelWidth()const
{
	if (GetModelHeight() == 0)
		return 0;
	return GetModel()[0].size();
}

void KinematicObject::Update()
{
	ApplyGravity();
}

void KinematicObject::ApplyGravity()
{
	double gravityScale = GetGravityScale();
	if (gravityScale == 0)
		return;
	if (gravityScale > 0)
		TryMove(Direction::down, gravityScale);
	else
		TryMove(Direction::up, gravityScale);
}

void KinematicObject::TryMove(Direction direction, double moveSpeed)
{
	if (canMove == false)
		return;

	moveSpeed = abs(moveSpeed);
	double deltaTime = TimeHelper::Instance().GetDeltaTime();

	switch (direction)
	{
	case Direction::up:
		yPosContinuous += moveSpeed * deltaTime;
		break;
	case Direction::down:
		yPosContinuous -= moveSpeed * deltaTime;
		break;
	case Direction::right:
		xPosContinuous += moveSpeed * deltaTime;
		break;
	case Direction::left:
		xPosContinuous -= moveSpeed * deltaTime;
		break;
	}

	if (direction == Direction::left || direction == Direction::right)
	{
		if (round(xPosContinuous) != xPos)
			Simulation::Instance().RequestMovement(this, direction, moveSpeed);
	}
	else if (round(yPosContinuous) != yPos)
		Simulation::Instance().RequestMovement(this, direction, moveSpeed);
}

Model KinematicObject::CreteModelUsingChar(char modelChar, size_t sizeX, size_t sizeY) const
{
	Model result;
	result.resize(sizeY);
	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			result[y].resize(sizeX);
			result[y][x] = modelChar;
		}
	}
	return result;
}

void KinematicObject::SetModel(const Model& newModel)
{
	if (model == &newModel)
		return;

	mustBeReprinted = true;
	model = &newModel;
}

void KinematicObject::CALLED_BY_SIM_Move(Direction direction)
{
	switch (direction)
	{
	case Direction::up:
		++yPos;
		yPosContinuous = yPos;
		break;
	case Direction::down:
		--yPos;
		yPosContinuous = yPos;
		break;
	case Direction::right:
		++xPos;
		xPosContinuous = xPos;
		break;
	case Direction::left:
		--xPos;
		xPosContinuous = xPos;
		break;
	}
	OnMove.Notify(this, direction);
}