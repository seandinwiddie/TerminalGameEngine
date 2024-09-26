#include "DebugManager.h"

#if DEBUG_MODE

void DebugManager::Reset
(
	size_t screenSizeX,
	size_t screenSizeY,
	size_t screenPadding
)
{
	fpsRecord.clear();
	fpsRecord.resize(0);
	coutCallsCount = 0;
	
	if (debugPrinter != nullptr)
		delete(debugPrinter);
	debugPrinter = new DebugPrinter(screenSizeX, screenSizeY, screenPadding);
}

void DebugManager::ShowAverageFPS()
{
	if(debugPrinter != nullptr)
		debugPrinter->PrintFpsString(GetAverageFps()); 
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

void DebugManager::IncrementCoutCalls()
{
	if (debugPrinter == nullptr)
		return;

	if (++coutCallsCount == 1000)
		coutCallsCount = 0;
	debugPrinter->PrintCoutCallsCount(coutCallsCount);
}

#endif