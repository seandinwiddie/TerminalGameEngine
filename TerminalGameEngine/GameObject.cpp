#include "GameObject.h"
#include "TimeHelper.h"
#include "Simulation.h"

GameObject::GameObject(int xPos, int yPos) : 
	xPos(xPos), 
	yPos(yPos), 
	xPosContinuous(xPos), 
	yPosContinuous(yPos)
{
	ResetPartialMovement();
}

uint GameObject::GetModelWidth() const
{
	if (model.size() == 0)
		return 0;

	return model[0].size();
}

void GameObject::Update()
{
	float gravityScale = GetGravityScale();
	if (gravityScale == 0)
		return;
	if (gravityScale > 0)
		Move(Direction::down, gravityScale);
	else
		Move(Direction::up, gravityScale);
}

void GameObject::Move(Direction direction, float moveSpeed)
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

std::vector<std::vector<char>> GameObject::CreteModelUsingChar
(
	char c, 
	uint sizeX, 
	uint sizeY
) const
{
	std::vector<std::vector<char>> result;
	result.resize(sizeY);
	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			result[y].resize(sizeX);
			result[y][x] = c;
		}
	}
	return result;
}

void GameObject::SetModel(const std::vector<std::vector<char>>& newModel)
{
	if (model == newModel)
		return;

	mustBeReprinted = true;
	model = newModel;
}

void GameObject::CALLED_BY_SIM_NotifyCollision(GameObject* other, Direction collisionDirection)
{
	int directionIndex = static_cast<int>(collisionDirection);
	if (collidingDirections[directionIndex] == false)
	{
		collidingDirections[directionIndex] = true;
		OnCollisionEnter(other, collisionDirection);
	}
}

void GameObject::CALLED_BY_SIM_UpdateCollidingDirecitons(const std::vector<bool>& newCollidingDirections)
{
	for (int i = 0; i < collidingDirections.size(); ++i)
	{
		if (collidingDirections[i] == true && newCollidingDirections[i] == false)
		{
			collidingDirections[i] = false;
			OnCollisionExit(static_cast<Direction>(i));
		}
	}
}

const std::vector<std::vector<char>>& GameObject::GetModel()
{
	if(!IsModelInitialized())
		InitModel();
	return model;
}