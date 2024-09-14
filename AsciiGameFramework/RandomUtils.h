#pragma once
#include "TimeUtils.h"
#include <cmath>

namespace RandomUtils
{
	static float GetRandomFloatBetween(const float min, const float max)
	{
		float r = rand() / static_cast<float>(RAND_MAX);
		return ((max - min) * r + min);
	}

	static int GetRandomIntBetween(const int min, const int max) { return min + std::rand() % (max - min + 1); }
}