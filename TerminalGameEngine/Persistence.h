#pragma once
#include <string>
#include <fstream>

namespace Persistence
{
	inline void SaveBestScore(const string& persistenceFile , int bestScore)
	{
		std::ofstream outStream(persistenceFile);
		assert(outStream);
		outStream << bestScore;
	}

	inline int LoadBestScore(const string& persistenceFile)
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

	inline int GetBestScoreConsideringNewOne(const string& persistenceFilePath,int newScore)
	{
		int bestScore = LoadBestScore(persistenceFilePath);
		if (newScore > bestScore)
		{
			bestScore = newScore;
			SaveBestScore(persistenceFilePath, newScore);
		}
		
		return bestScore;
	}
}