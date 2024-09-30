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
}