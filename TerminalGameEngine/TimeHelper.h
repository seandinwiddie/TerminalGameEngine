#pragma once

#include "Singleton.h"

#include <chrono>
#include <math.h>

using time_point = std::chrono::steady_clock::time_point;
using hr_clock = std::chrono::high_resolution_clock;

class TimeHelper : public Singleton<TimeHelper>
{
friend class Singleton;

//---------------------------------------------------------- Fields
private:
    time_point startTime;
    double lastTimeFrameGenerated = 0;
    double deltaTime = 1;

//---------------------------------------------------------- Methods
public:
    double GetDeltaTime() const { return deltaTime; }
    double GetFPS() const { return 1.0 / GetDeltaTime(); }

    void NotifyFrameGenerated ();
    bool IsTimeForFirstOfTwoModels (double changeModelEverySeconds) const;
    double GetTime() const;

private:
    TimeHelper() {startTime = hr_clock::now(); }
};