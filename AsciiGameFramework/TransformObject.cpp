#include "TransformObject.h"
#include "TimeUtils.h"
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
		Move(Direction::down, gravityScale);
	else
		Move(Direction::up, gravityScale);
}

void TransformObject::Move(Direction direction, float moveSpeed)
{
	if (canMove == false)
		return;

	double deltaTime = TimeUtils::Instance().GetDeltaTime();
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
		{
			if (Simulation::Instance().TryMoveAtDirection(this, direction))
				lastTimeMovedInGrid = TimeUtils::Instance().GetTime();

			xPosContinuous = xPos;
		}
	}
	else
	{
		if (round(yPosContinuous) != yPos)
		{
			if (Simulation::Instance().TryMoveAtDirection(this, direction))
				lastTimeMovedInGrid = TimeUtils::Instance().GetTime();

			yPosContinuous = yPos;
		}
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

