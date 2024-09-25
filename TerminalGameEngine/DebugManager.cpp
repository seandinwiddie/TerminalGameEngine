#include "DebugManager.h"

#if DEBUG_MODE

void DebugManager::Reset()
{
	fpsRecord.clear();
	fpsRecord.resize(0);
	coutCalls = 0;
}

size_t DebugManager::GetAverageFps()
{
	double fps = TimeHelper::Instance().GetFPS();
	fpsRecord.push_back(fps);

	if (TimeHelper::Instance().GetTime() - lastTimePrintedFps > REFRESH_FPS_EVERY_SECONDS)
	{
		averageFPS = 0;

		for (double fps : fpsRecord)
			averageFPS += fps;
		averageFPS /= fpsRecord.size();

		fpsRecord.clear();
		lastTimePrintedFps = TimeHelper::Instance().GetTime();
	}
	return static_cast<size_t>(averageFPS);
}

size_t DebugManager::IncreaseCoutCalls()
{
	if (coutCalls == 1000)
		coutCalls = 0;

	return ++coutCalls;
}

#endif