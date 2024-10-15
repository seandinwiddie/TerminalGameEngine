#pragma once
#include <string>

namespace StringUtils
{
	using string = std::string;

	void RemoveInstancesOfChar(string& str, char charToRemove)
	{
		str.erase(std::remove(str.begin(), str.end(), charToRemove), str.end());
	}
}