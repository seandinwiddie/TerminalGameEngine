#pragma once
#include "Config.h"

#if DEBUG_MODE

#include "Terminal.h"
#include "Singleton.h"
#include "TimeHelper.h"
#include "Simulation.h"
#include <list>
#include <string>

using string = std::string;

class DebugManager : public Singleton<DebugManager>
{
	friend class Singleton;

//---------------------------------------------------------- Settings
private:
	static constexpr double REFRESH_FPS_EVERY_SECONDS = 0.5;
//---------------------------------------------------------- Fields
private:
	//fps
	std::list<double> fpsRecord;
	double lastTimePrintedFps = 0;
	size_t averageFPS = 0;

	//cout calls
	int coutCalls = 0;
//---------------------------------------------------------- Methods
public:
	void Reset();
	size_t GetAverageFps();
	size_t IncreaseCoutCalls();
};

#endif