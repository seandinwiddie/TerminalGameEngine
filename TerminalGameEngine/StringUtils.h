#pragma once
#include <string>

using string = std::string;

namespace StringUtils
{
	void RemoveInstancesOfChar(string& str, char charToRemove)
	{
		str.erase(std::remove(str.begin(), str.end(), charToRemove), str.end());
	}
}