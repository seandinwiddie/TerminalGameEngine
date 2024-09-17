#pragma once

#include "Singleton.h"

#include <chrono>
#include <math.h>

using TimePoint = std::chrono::steady_clock::time_point;

class TimeUtils : public Singleton<TimeUtils>
{
    friend class Singleton;

//---------------------------------------------------------- Fields
private:
    TimePoint startTime;
    double lastTimeFrameGenerated = 0;
    double deltaTime = 1;

//---------------------------------------------------------- Methods
public:
    double GetDeltaTime() const { return deltaTime; }
    double GetFPS() const { return 1.0 / GetDeltaTime(); }

    void NotifyFrameGenerated ();
    bool IsTimeForFirstOfTwoModels (float changeModelEverySeconds) const;
    double GetTime() const;

private:
    TimeUtils() {startTime = std::chrono::high_resolution_clock::now(); }
};