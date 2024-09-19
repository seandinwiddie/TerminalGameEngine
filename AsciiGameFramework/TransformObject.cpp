#include "TransformObject.h"
#include "TimeHelper.h"
#include "Simulation.h"

TransformObject::TransformObject(int xPos, int yPos) : 
	xPos(xPos), 
	yPos(yPos), 
	xPosContinuous(xPos), 
	yPosContinuous(yPos)
{
	ResetPartialMovement();
}

uint TransformObject::GetModelWidth() const
{
	if (model.size() == 0)
		return 0;

	return model[0].size();
}

void TransformObject::Update()
{
	float gravityScale = GetGravityScale();
	if (gravityScale == 0)
		return;
	if (gravityScale > 0)
		MoveContinuous(Direction::down, gravityScale);
	else
		MoveContinuous(Direction::up, gravityScale);
}

void TransformObject::MoveContinuous(Direction direction, float moveSpeed)
{
	if (canMove == false)
		return;

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
			Simulation::Instance().RequestDiscreteMovement(this, direction, moveSpeed);
	}
	else if (round(yPosContinuous) != yPos)
		Simulation::Instance().RequestDiscreteMovement(this, direction, moveSpeed);
}

//todo discrete position could be saved inside simulation so objects cannot modify it
void TransformObject::SIM_MoveDiscrete(Direction direction)
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
}

std::vector<std::vector<char>> TransformObject::CreteModelUsingChar
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

