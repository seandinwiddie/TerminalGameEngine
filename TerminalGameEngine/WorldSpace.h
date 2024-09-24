#pragma once
#include "GridDirection.h"

#include <vector>

using Direction = GridDirection::Direction;
template<typename T> using vector = std::vector<T>;

class GameObject;

class WorldSpace
{
//---------------------------------------------------------- Fields
private:
	vector<vector<GameObject*>> space;
//---------------------------------------------------------- Methods
public:
	void Init(int xSize, int ySize);

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