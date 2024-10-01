#include "WorldSpace.h"
#include "GameObject.h"

FakeGameObject WorldSpace::WORLD_MARGIN_MEMORY;
FakeGameObject WorldSpace::SCREEN_MARGIN_MEMORY;

FakeGameObject* WorldSpace::WORLD_MARGIN = &WorldSpace::WORLD_MARGIN_MEMORY;
FakeGameObject* WorldSpace::SCREEN_MARGIN = &WorldSpace::SCREEN_MARGIN_MEMORY;

void WorldSpace::Init(int xSize, int ySize, size_t screenPadding)
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

bool WorldSpace::IsAreaEmpty(int startingX, int startingY, size_t width, size_t height, uset<GameObject*>& areaObjects) const
{
	for (int y = startingY; y < startingY + height; ++y)
		for (int x = startingX; x < startingX + width; ++x)
			if (IsCoordinateInsideSpace(x, y) && space[y][x] != nullptr)
				areaObjects.insert(space[y][x]);

	return areaObjects.size() == 0;
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
	const KinematicObject* kinObj,
	Direction direction,
	uset<GameObject*>& collidingObjects
) const
{
	const GameObject* gameObj = dynamic_cast<const GameObject*>(kinObj);

	switch (direction)
	{
	case Direction::up:
	{
		int movingToY = kinObj->GetMaxPosY() + 1;

		//exiting world
		if (movingToY == GetSizeY())
		{
			collidingObjects.insert(WORLD_MARGIN);
			return false;
		}

		//exiting screen space
		if ((kinObj->CanExitScreenSpace() == false) && (movingToY == GetSizeY() - screenPadding))
		{
			collidingObjects.insert(SCREEN_MARGIN);
			return false;
		}

		//obj collision
		if (gameObj != nullptr && IsAreaEmpty(gameObj->GetPosX(), movingToY, gameObj->GetModelWidth(), 1, collidingObjects) == false)
			return false;
		
		return true;
	}
	case Direction::down:
	{
		int movingToY = kinObj->GetPosY() - 1;

		//exiting world
		if (movingToY == -1)
		{
			collidingObjects.insert(WORLD_MARGIN);
			return false;
		}

		//exiting screen space
		if ((kinObj->CanExitScreenSpace() == false) && (movingToY == screenPadding - 1))
		{
			collidingObjects.insert(SCREEN_MARGIN);
			return false;
		}

		//obj collision
		if (gameObj != nullptr && IsAreaEmpty(gameObj->GetPosX(), movingToY, gameObj->GetModelWidth(), 1, collidingObjects) == false)
			return false;

		return true;
	}
	case Direction::right:
	{
		int movingToX = kinObj->GetMaxPosX() + 1;

		//exiting world
		if (movingToX == GetSizeX())
		{
			collidingObjects.insert(WORLD_MARGIN);
			return false;
		}

		//exiting screen space
		if ((kinObj->CanExitScreenSpace() == false) && (movingToX == GetSizeX() - screenPadding))
		{
			collidingObjects.insert(SCREEN_MARGIN);
			return false;
		}

		//obj collision
		if (gameObj != nullptr && IsAreaEmpty(movingToX, gameObj->GetPosY(), 1, gameObj->GetModelHeight(), collidingObjects) == false)
			return false;

		return true;
	}
	case Direction::left:
	{
		int movingToX = kinObj->GetPosX() - 1;

		//exiting world
		if (movingToX == -1)
		{
			collidingObjects.insert(WORLD_MARGIN);
			return false;
		}

		//exiting screen space
		if ((kinObj->CanExitScreenSpace() == false) && (movingToX == screenPadding - 1))
		{
			collidingObjects.insert(SCREEN_MARGIN);
			return false;
		}

		//obj collision
		if (gameObj != nullptr && IsAreaEmpty(movingToX, gameObj->GetPosY(), 1, gameObj->GetModelHeight(), collidingObjects) == false)
			return false;

		return true;
	}
	default:
		throw std::invalid_argument("Invalid direction");
	}
}