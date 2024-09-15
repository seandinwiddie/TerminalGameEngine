#pragma once
#include <string>
#include <fstream>
#include <cassert>

namespace Persistence
{
	static void SaveBestScore(const string& persistenceFile ,const int bestScore)
	{
		std::ofstream outStream(persistenceFile);
		assert(outStream);
		outStream << bestScore;
	}

	static int LoadBestScore(const string& persistenceFile)
	{
		std::ifstream infile(persistenceFile);

		if (!infile)
		{
			SaveBestScore(persistenceFile, -1);
			return -1;
		}
		
		int bestScore;
		infile >> bestScore;
		return bestScore;
	}
}