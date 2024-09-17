#pragma once
#include "TimeUtils.h"
#include <cmath>

namespace RandomUtils
{
	static float GetRandomFloatBetween(float min, float max)
	{
		float r = rand() / static_cast<float>(RAND_MAX);
		return ((max - min) * r + min);
	}

	static int GetRandomInt(int minInclusive, int maxInclusive) 
	{ 
		return minInclusive + std::rand() % (maxInclusive - minInclusive + 1); 
	}
}