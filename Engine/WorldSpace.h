#pragma once
#include "DirectionUtils.h"
#include "FakeCollider.h"
#include "Vector2D.h"

#include <cassert>
#include <unordered_set>
#include <set>

namespace Engine
{
	template<typename T> using uset = std::unordered_set<T>;
	template<typename T> using list = std::list<T>;

	class WorldSpace
	{
		//---------------------------------------------------------- Structs
	private:
		struct Cell
		{
			// cell collider, max 1 for cell
			Collider* collider = nullptr;	

			// all objects in cell, including collider if present
			// (using list cause there are a lot of small sets (2/3 elements max per list usually)
			list<GameObject*> objects;
		};

		//---------------------------------------------------------- Margins
	public:
		static FakeCollider* WORLD_MARGIN;
		static FakeCollider* SCREEN_MARGIN;
	private:
		static FakeCollider WORLD_MARGIN_MEMORY;
		static FakeCollider SCREEN_MARGIN_MEMORY;

		//---------------------------------------------------------- Fields
	public:
		Vector2D<Cell> space;
		size_t screenPadding;
		//---------------------------------------------------------- Methods
	public:
		void Init(int xSize, int ySize, size_t screenPadding);

		bool CanObjectMoveAtDirection(const GameObject* obj, Direction direction, uset<Collider*>& collidingObjects) const;
		void InsertObject(GameObject* obj);
		void RemoveObject(GameObject* obj);
		void MoveObject(GameObject* obj, Direction direction);
		bool IsCoordinateInsideSpace(int xPos, int yPos) const;
		bool IsInsideSpaceX(int xPos) const;
		bool IsInsideSpaceY(int yPos) const;

		bool IsCollidersAreaEmpty(int startingX, int startingY, size_t width, size_t height, uset<Collider*>& areaObjects) const;
		bool IsCollidersAreaEmpty(int startingX, int startingY, size_t width, size_t height) const;

		uset<GameObject*> GetAreaTopLayerObjects(GameObject* obj);
		uset<GameObject*> GetAreaTopLayerObjects(int startingX, int startingY, size_t width, size_t height);

	private:
		void WriteSpace(int xStart, int yStart, size_t width, size_t height, GameObject* value);
		void EraseSpace(int xStart, int yStart, size_t width, size_t height, GameObject* value);		
	};
}