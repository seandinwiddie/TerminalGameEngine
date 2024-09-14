#include "GameObject.h"
#include "TimeUtils.h"
#include "Simulation.h"

GameObject::GameObject(const int xPos, const int yPos) : 
	xPos(xPos), 
	yPos(yPos), 
	xPosContinuous(xPos), 
	yPosContinuous(yPos)
{
	ResetPartialMovement();
}

int GameObject::GetModelWidth() const
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
//todo check this is not called often
std::vector<std::vector<unsigned char>> GameObject::CreteModelUsingChar
(
	unsigned char c, 
	const unsigned int sizeX, 
	const unsigned int sizeY
) const
{
	std::vector<std::vector<unsigned char>> result;
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

