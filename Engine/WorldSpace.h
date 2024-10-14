#pragma once
#include "GridDirection.h"
#include "FakeCollider.h"
#include "Vector2D.h"

#include <cassert>
#include <unordered_set>
#include <set>

namespace Engine
{
	template<typename T> using uset = std::unordered_set<T>;
	template<typename T> using multiset = std::multiset<T>;

	class WorldSpace
	{
		//---------------------------------------------------------- Structs
	private:
		struct SortingRule
		{
			bool operator()(GameObject* a, GameObject* b) const
			{
				return a->GetSortingOrder() > b->GetSortingOrder(); // Descending order
			}
		};
		struct Cell
		{
			Collider* collider = nullptr;	// cell collider, max 1 for cell
			std::multiset<GameObject*, SortingRule> objects; 		// all objects in cell, includeing collider if present
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

		uset<GameObject*> GetAreaObjects(GameObject* obj);
		uset<GameObject*> GetAreaObjects(int startingX, int startingY, size_t width, size_t height);

	private:
		void WriteSpace(int xStart, int yStart, size_t width, size_t height, GameObject* value);
		void EraseSpace(int xStart, int yStart, size_t width, size_t height, GameObject* value);		
	};
}