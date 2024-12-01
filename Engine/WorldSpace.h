#pragma once
#include "DirectionUtils.h"
#include "FakeCollider.h"
#include "Vector2D.h"
#include <memory>

#include <cassert>
#include <unordered_set>
#include <set>

namespace Engine
{
	template<typename T> using uset = std::unordered_set<T>;
	template<typename T> using list = std::list<T>;
	template<typename T> using shared_ptr = std::shared_ptr<T>;
	template<typename T> using weak_ptr = std::weak_ptr<T>;

	class WorldSpace
	{
		//---------------------------------------------------------- Structs
	private:
		struct Cell
		{
			// cell collider, max 1 for cell
			weak_ptr<Collider> collider;	

			// all objects in cell, including collider if present
			// (using list cause there are a lot of small sets (2/3 elements max per list usually)
			list<weak_ptr<GameObject>> objects;
		};

		//---------------------------------------------------------- Margins
	public:
		static shared_ptr<FakeCollider> WORLD_MARGIN;
		static shared_ptr<FakeCollider> SCREEN_MARGIN;

		//---------------------------------------------------------- Fields
	public:
		Vector2D<Cell> space;
		size_t screenPadding;
		//---------------------------------------------------------- Methods
	public:
		void Init(int xSize, int ySize, size_t screenPadding);

		bool CanObjectMoveAtDirection(shared_ptr<const GameObject> obj, Direction direction, uset<shared_ptr<Collider>>& collidingObjects) const;
		void InsertObject(shared_ptr<GameObject> obj);
		void RemoveObject(shared_ptr<GameObject> obj);
		void MoveObject(shared_ptr<GameObject> obj, Direction direction);
		bool IsCoordinateInsideSpace(int xPos, int yPos) const;
		bool IsInsideSpaceX(int xPos) const;
		bool IsInsideSpaceY(int yPos) const;

		bool IsCollidersAreaEmpty(int startingX, int startingY, size_t width, size_t height, uset<shared_ptr<Collider>>& outAreaObjects) const;
		bool IsCollidersAreaEmpty(int startingX, int startingY, size_t width, size_t height) const;

		uset<shared_ptr<GameObject>> GetAreaTopLayerObjects(shared_ptr<GameObject> obj);
		uset<shared_ptr<GameObject>> GetAreaTopLayerObjects(int startingX, int startingY, size_t width, size_t height);

	private:
		void WriteSpace(int xStart, int yStart, size_t width, size_t height, shared_ptr<GameObject> value);
		void EraseSpace(int xStart, int yStart, size_t width, size_t height, shared_ptr<GameObject> value);
	};
}