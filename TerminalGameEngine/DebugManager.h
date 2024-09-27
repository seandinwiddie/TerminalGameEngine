#pragma once
#include "Config.h"

#if DEBUG_MODE

#include "Singleton.h"

#include <list>
#include <string>

using string = std::string;

class DebugPrinter;

class DebugManager : public Singleton<DebugManager>
{
friend class Singleton;
//---------------------------------------------------------- Settings
private:
	static constexpr double REFRESH_FPS_EVERY_SECONDS = 0.5;
//---------------------------------------------------------- Fields
	DebugPrinter* debugPrinter = nullptr;

	//fps
	std::list<double> fpsRecord;
	double lastTimePrintedFps = 0;
	size_t averageFPS = 0;

	//cout calls
	int coutCallsCount = 0;
//---------------------------------------------------------- Methods
public:
	void Reset(size_t screenSizeX, size_t screenSizeY, size_t screenPadding);
	void ShowAverageFPS();
	void IncrementCoutCalls();
	void PrintGenericLog(const string& str);

private:
	size_t GetAverageFps();
};
#endif