#pragma once
#include <string>
#include <fstream>
#include <cassert>

namespace Persistence
{
	static const string PERSISTENCE_FILE_NAME = "persistence.txt";

	static void SaveBestScore(const int bestScore)
	{
		std::ofstream outStream(PERSISTENCE_FILE_NAME);
		assert(outStream);
		outStream << bestScore;
	}

	static int LoadBestScore()
	{
		std::ifstream infile(PERSISTENCE_FILE_NAME);

		if (!infile)
		{
			SaveBestScore(-1);
			return -1;
		}
		
		int bestScore;
		infile >> bestScore;
		return bestScore;
	}
}