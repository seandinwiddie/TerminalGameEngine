#include "WorldSpace.h"
#include "GameObject.h"

FakeGameObject WorldSpace::WORLD_MARGIN;
FakeGameObject WorldSpace::SCREEN_MARGIN;

void WorldSpace::Init(int xSize, int ySize, int screenPadding)
{
	space.clear();
	space.resize(ySize);
	for (int y = 0; y < ySize; ++y)
	{
		space[y].resize(xSize);
		for (GameObject* elem : space[y])
			elem = nullptr;
	}
	this->screenPadding = screenPadding;
}

void WorldSpace::InsertObject(GameObject* obj)
{
	WriteSpace(obj->GetPosX(), obj->GetPosY(), obj->GetModelWidth(), obj->GetModelHeight(), obj);
}

void WorldSpace::RemoveObject(GameObject* obj)
{
	WriteSpace(obj->GetPosX(), obj->GetPosY(), obj->GetModelWidth(), obj->GetModelHeight(), nullptr);
}

void WorldSpace::MoveObject(GameObject* obj, Direction direction)
{
	switch (direction)
	{
		case Direction::up:
		{
			int yWrite = obj->GetMaxPosY() + 1;
			int yClear = obj->GetPosY();
			WriteSpace(obj->GetPosX(), yWrite, obj->GetModelWidth(), 1, obj);
			WriteSpace(obj->GetPosX(), yClear, obj->GetModelWidth(), 1, nullptr);
			break;
		}
		case Direction::down:
		{
			int yWrite = obj->GetPosY() - 1;
			int yClear = obj->GetMaxPosY();
			WriteSpace(obj->GetPosX(), yWrite, obj->GetModelWidth(), 1, obj);
			WriteSpace(obj->GetPosX(), yClear, obj->GetModelWidth(), 1, nullptr);
			break;
		}
		case Direction::right:
		{
			int xWrite = obj->GetMaxPosX() + 1;
			int xClear = obj->GetPosX();
			WriteSpace(xWrite, obj->GetPosY(), 1, obj->GetModelHeight(), obj);
			WriteSpace(xClear, obj->GetPosY(), 1, obj->GetModelHeight(), nullptr);
			break;
		}

		case Direction::left:
		{
			int xWrite = obj->GetPosX() - 1;
			int xClear = obj->GetMaxPosX();
			WriteSpace(xWrite, obj->GetPosY(), 1, obj->GetModelHeight(), obj);
			WriteSpace(xClear, obj->GetPosY(), 1, obj->GetModelHeight(), nullptr);
			break;
		}
	}
}

void WorldSpace::WriteSpace(int xStart, int yStart, size_t width, size_t height, GameObject* value)
{
	for (int y = yStart; y < yStart + height; ++y)
	{
		for (int x = xStart; x < xStart + width; ++x)
		{
			space[y][x] = value;
		}
	}
}

bool WorldSpace::IsAreaEmpty(int startingX, int startingY, size_t width, size_t height) const
{
	for (int y = startingY; y < startingY + height; ++y)
		for (int x = startingX; x < startingX + width; ++x)
			if (IsCoordinateInsideSpace(x, y) && space[y][x] != nullptr)
				return false;
	return true;
}


bool WorldSpace::IsCoordinateInsideSpace(int xPos, int yPos) const
{
	return IsInsideSpaceX(xPos) && IsInsideSpaceY(yPos);
}


bool WorldSpace::IsInsideSpaceX(int xPos) const
{
	return xPos >= 0 && xPos < GetSizeX();
}

bool WorldSpace::IsInsideSpaceY(int yPos) const
{
	return yPos >= 0 && yPos < GetSizeY();
}

bool WorldSpace::CanObjectMoveAtDirection
(
	const GameObject* obj,
	Direction direction,
	GameObject*& outCollidingObject
) const
{
	switch (direction)
	{
	case Direction::up:
	{
		int y = obj->GetMaxPosY() + 1;

		//exiting world
		if (y == GetSizeY())
		{
			outCollidingObject = &WORLD_MARGIN;
			return false;
		}

		//exiting screen space
		if (obj->CanExitScreenSpace() == false)
		{
			if (y == GetSizeY() - screenPadding)
			{
				outCollidingObject = &SCREEN_MARGIN;
				return false;
			}
		}

		//obj collision
		for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); x++)
		{
			if (IsPositionEmpty(x, y) == false)
			{
				outCollidingObject = GetObjectAtPosition(x, y);
				return false;
			}
		}

		return true;
	}
	case Direction::down:
	{
		int y = obj->GetPosY() - 1;

		if (y == -1)
		{
			outCollidingObject = &WORLD_MARGIN;
			return false;
		}

		//exiting screen space
		if (obj->CanExitScreenSpace() == false)
		{
			if (y == screenPadding - 1)
			{
				outCollidingObject = &SCREEN_MARGIN;
				return false;
			}
		}

		//obj collision
		for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); x++)
		{
			if (IsPositionEmpty(x, y) == false)
			{
				outCollidingObject = GetObjectAtPosition(x, y);
				return false;
			}
		}

		return true;
	}
	case Direction::right:
	{
		int x = obj->GetMaxPosX() + 1;

		if (x == GetSizeX())
		{
			outCollidingObject = &WORLD_MARGIN;
			return false;
		}

		//exiting screen space
		if (obj->CanExitScreenSpace() == false)
		{
			if (x == GetSizeX() - screenPadding)
			{
				outCollidingObject = &SCREEN_MARGIN;
				return false;
			}
		}

		//obj collision
		for (int y = obj->GetPosY(); y <= obj->GetMaxPosY(); y++)
		{
			if (IsPositionEmpty(x, y) == false)
			{
				outCollidingObject = GetObjectAtPosition(x, y);
				return false;
			}
		}

		return true;
	}
	case Direction::left:
	{
		int x = obj->GetPosX() - 1;

		if (x == -1)
		{
			outCollidingObject = &WORLD_MARGIN;
			return false;
		}

		//exiting screen space
		if (obj->CanExitScreenSpace() == false)
		{
			if (x == screenPadding - 1)
			{
				outCollidingObject = &SCREEN_MARGIN;
				return false;
			}
		}

		// obj collision
		for (int y = obj->GetPosY(); y <= obj->GetMaxPosY(); y++)
		{
			if (IsPositionEmpty(x, y) == false)
			{
				outCollidingObject = GetObjectAtPosition(x, y);
				return false;
			}
		}

		return true;
	}
	default:
		throw std::invalid_argument("Invalid direction");
	}
}