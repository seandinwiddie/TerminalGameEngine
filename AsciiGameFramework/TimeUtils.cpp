#pragma once

#include "TimeUtils.h"

void TimeUtils::NotifyFrameGenerated()
{
    double currentTime = GetTime();
    deltaTime = currentTime - lastTimeFrameGenerated;
    lastTimeFrameGenerated = currentTime;
}

bool TimeUtils::IsTimeForFirstOfTwoModels(float changeModelEverySeconds) const
{
    double time = GetTime();

    if (time == 0)
        return false;

    return fmod(time, changeModelEverySeconds) < changeModelEverySeconds / 2;
}

double TimeUtils::GetTime() const
{
    // Get the current time
    TimePoint now = std::chrono::high_resolution_clock::now();

    // Calculate the duration in seconds
    std::chrono::duration<double> elapsed = now - startTime;
    return elapsed.count();
}