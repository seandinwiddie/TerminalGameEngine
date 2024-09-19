#pragma once
#include "TimeHelper.h"
#include <cmath>

namespace RandomUtils
{
	inline float GetRandomFloatBetween(float min, float max)
	{
		float r = rand() / static_cast<float>(RAND_MAX);
		return ((max - min) * r + min);
	}

	inline int GetRandomInt(int minInclusive, int maxInclusive) 
	{ 
		return minInclusive + std::rand() % (maxInclusive - minInclusive + 1); 
	}
}