#pragma once
#include "GameObject.h"
#include <optional>

namespace Platformer
{
	using Engine::Direction;

	class SortingLayerTestObject : public Engine::GameObject
	{
	private:
		size_t sizeX;
		size_t sizeY;
		char modelChar;
		int color;
		size_t sortingLayer;
		double moveSpeed;
		std::optional<Direction> mainDirection;

		Engine::Model model;

	public:
		SortingLayerTestObject
		(
			int xPos,
			int yPos,
			size_t sizeX,
			size_t sizeY,
			char modelChar,
			int color,
			size_t sortingLayer,
			double moveSpeed = 0,
			std::optional<Direction> mainDirection = std::nullopt
		);

		bool CanExitScreenSpace() const override { return true; }
		double GetGravityScale() const override { return 0; }
		virtual int GetColor() const { return color; }
		virtual size_t GetSortingLayer() const { return sortingLayer; }

	protected:
		virtual void InitModel();
		virtual void Update();
	};
}