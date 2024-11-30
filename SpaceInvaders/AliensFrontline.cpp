#include "AliensFrontline.h"
#include "Alien.h"

namespace SpaceInvaders
{
	size_t AliensFrontline::GetMinY()
	{
		size_t min = SIZE_MAX;
		for (shared_ptr<Alien> alien : frontLine)
			if (alien != nullptr && alien->GetPosY() < min)
				min = alien->GetPosY();

		return min;
	}

	void AliensFrontline::ReplaceDestroyedElement(shared_ptr<Alien> destroyedAlien, const Vector2D<shared_ptr<Alien>>& aliensGrid)
	{
		size_t destroyedX = destroyedAlien->GetIndexInGridX();

		if (frontLine[destroyedX] != destroyedAlien)
			return;

		//try find new front line element
		for (int y = static_cast<int>(aliensGrid.GetSizeY()) - 1; y >= 0; --y)
		{
			if (aliensGrid.Get(destroyedX, y) != nullptr)
			{
				frontLine[destroyedX] = aliensGrid.Get(destroyedX, y);
				return;
			}
		}

		//whole column eliminated
		frontLine[destroyedX] = nullptr;
	}

	shared_ptr<Alien> AliensFrontline::GetRandom()
	{
		return GetAt(RandomUtils::GetRandomInt(0, static_cast<int>(frontLine.size()) - 1));
	}
}