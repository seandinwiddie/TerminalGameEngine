#pragma once
#include "GridDirection.h"
#include "FakeCollider.h"

#include <vector>
#include <cassert>
#include <unordered_set>

using Direction = GridDirection::Direction;
template<typename T> using vector = std::vector<T>;
template<typename T> using uset = std::unordered_set<T>;

class WorldSpace
{
//---------------------------------------------------------- Margins
public:
	static FakeCollider* WORLD_MARGIN;
	static FakeCollider* SCREEN_MARGIN;
private:
	static FakeCollider WORLD_MARGIN_MEMORY;
	static FakeCollider SCREEN_MARGIN_MEMORY;

//---------------------------------------------------------- Fields
public:
	vector<vector<Collider*>> space;
	size_t screenPadding;
//---------------------------------------------------------- Methods
public:
	void Init(int xSize, int ySize, size_t screenPadding);

	bool CanObjectMoveAtDirection(const GameObject* obj, Direction direction, uset<Collider*>& collidingObjects) const;
	void InsertObject(Collider* obj);
	void RemoveObject(Collider* obj);
	void MoveObject(Collider* obj, Direction direction);
	bool IsCoordinateInsideSpace(int xPos, int yPos) const;
	bool IsInsideSpaceX(int xPos) const;
	bool IsInsideSpaceY(int yPos) const;

	// this returns only first colliding object found
	// may be improved returning list of all colliding objects
	// at the moment if an objects collides with many objects during same step, only one of the collisions is triggered
	// (for now its ok cause im using only small objects and levels dont produce this kind of collision)
	bool IsAreaEmpty(int startingX, int startingY, size_t width, size_t height, uset<Collider*>& areaObjects) const;
	bool IsAreaEmpty(int startingX, int startingY, size_t width, size_t height) const;

private:
	void WriteSpace(int xStart, int yStart, size_t width, size_t height, Collider* value);
	size_t GetSizeX()const { return GetSizeY() == 0 ? 0 : space[0].size(); }
	size_t GetSizeY()const { return space.size(); }
};