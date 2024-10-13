#pragma once
#include <stdexcept>
#include <cassert>

namespace Engine
{
	enum Direction { up, down, left, right, COUNT };

	inline Direction GetInverseDirection(Direction direction)
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

	inline Direction GetClockwiseDirection(Direction direction)
	{
		switch (direction)
		{
		case Direction::up:
			return Direction::right;
		case Direction::down:
			return Direction::left;
		case Direction::left:
			return Direction::up;
		case Direction::right:
			return Direction::down;
		default:
			throw std::invalid_argument("Invalid direction");
		}
	}

	inline bool IsHorizzontal(Direction dir)
	{ 
		assert(dir != Direction::COUNT);
		return dir == Direction::left || dir == Direction::right; 
	}

}