#pragma once

namespace GridDirection
{
	enum class Direction { up, down, left, right, COUNT };

	static Direction GetInverseDirection(const Direction direction)
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
		}
	}
}