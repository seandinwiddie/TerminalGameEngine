#pragma once
#include "GridDirection.h"
#include "FakeGameObejct.h"

#include <vector>
#include <cassert>

using Direction = GridDirection::Direction;
template<typename T> using vector = std::vector<T>;

class WorldSpace
{
//---------------------------------------------------------- Fields
public:
	static FakeGameObject WORLD_MARGIN;
	static FakeGameObject SCREEN_MARGIN;

	vector<vector<GameObject*>> space;
	int screenPadding;
//---------------------------------------------------------- Methods
public:
	void Init(int xSize, int ySize, int screenPadding);

	bool CanObjectMoveAtDirection(const GameObject* obj, Direction direction, GameObject*& outCollidingObject) const;
	void InsertObject(GameObject* obj);
	void RemoveObject(GameObject* obj);
	void MoveObject(GameObject* obj, Direction direction);
	bool IsAreaEmpty(int startingX, int startingY, size_t width, size_t height) const;
	bool IsPositionEmpty(int xPos, int yPos)const { return GetObjectAtPosition(xPos, yPos) == nullptr; }
	GameObject* GetObjectAtPosition(int xPos, int yPos)const { return space[yPos][xPos]; }
	bool IsCoordinateInsideSpace(int xPos, int yPos) const;
	bool IsInsideSpaceX(int xPos) const;
	bool IsInsideSpaceY(int yPos) const;

private:
	void WriteSpace(int xStart, int yStart, size_t width, size_t height, GameObject* value);
	size_t GetSizeX()const { return GetSizeY() == 0 ? 0 : space[0].size(); }
	size_t GetSizeY()const { return space.size(); }
};