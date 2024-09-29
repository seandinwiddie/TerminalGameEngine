#pragma once
#include <string>
#include <fstream>

namespace Persistence
{
	inline void SaveBestScore(const string& persistenceFile , size_t bestScore)
	{
		std::ofstream outStream(persistenceFile);
		assert(outStream);
		outStream << bestScore;
	}

	inline size_t LoadBestScore(const string& persistenceFile)
	{
		std::ifstream infile(persistenceFile);

		if (!infile)
		{
			SaveBestScore(persistenceFile, -1);
			return -1;
		}
		
		size_t bestScore;
		infile >> bestScore;
		return bestScore;
	}

	inline size_t GetBestScoreComparingToNewOne(const string& persistenceFilePath,size_t newScore)
	{
		size_t bestScore = LoadBestScore(persistenceFilePath);
		if (newScore > bestScore)
		{
			bestScore = newScore;
			SaveBestScore(persistenceFilePath, newScore);
		}
		
		return bestScore;
	}
}