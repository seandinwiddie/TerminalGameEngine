#pragma once

#include "TimeHelper.h"
#include "Simulation.h"

void TimeHelper::OnFrameGenerated()
{
    double currentTime = GetTime();
    deltaTime = currentTime - lastTimeFrameGenerated;
    lastTimeFrameGenerated = currentTime;
}

bool TimeHelper::IsTimeForFirstOfTwoModels(double changeModelEverySeconds) const
{
    double time = GetTime();

    if (time == 0)
        return false;

    return fmod(time, changeModelEverySeconds) < changeModelEverySeconds / 2;
}

double TimeHelper::GetTime() const
{
    time_point now = hr_clock::now();
    std::chrono::duration<double> elapsed = now - startTime;
    return elapsed.count();
}

TimeHelper::TimeHelper()
{
    Simulation::Instance().OnFrameGenerated.Subscribe( [this]() { OnFrameGenerated(); });
    startTime = hr_clock::now();
}