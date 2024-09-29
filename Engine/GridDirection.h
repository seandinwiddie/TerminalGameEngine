#pragma once
#include <stdexcept>

namespace GridDirection
{
	enum Direction { up, down, left, right, COUNT };

	static Direction GetInverseDirection(Direction direction)
	{
		switch (direction)
		{
		case Direction::up:
			return Direction::down;
		case Direction::down:
			return Direction::up;
		case Direction::left:
			return Direction::right;
		case Direction::right:
			return Direction::left;
		default:
			throw std::invalid_argument("Invalid direction");
		}
	}
}