#include "AliensFrontline.h"
#include "Alien.h"

namespace SpaceInvaders
{
	size_t AliensFrontline::GetMinY()
	{
		size_t min = SIZE_MAX;
		for (Alien* alien : frontLine)
			if (alien != nullptr && alien->GetPosY() < min)
				min = alien->GetPosY();

		return min;
	}

	void AliensFrontline::ReplaceDestroyedElement(Alien* destroyedAlien, const Vector2D<Alien*>& aliensGrid)
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

	Alien* AliensFrontline::GetRandom()
	{
		return GetAt(RandomUtils::GetRandomInt(0, static_cast<int>(frontLine.size()) - 1));
	}
}