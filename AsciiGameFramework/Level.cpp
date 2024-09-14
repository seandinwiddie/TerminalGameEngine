#include "Level.h"

double Level:: GetLevelTime() const
{
    if (IsGameOver())
        return gameOverTime - levelStartedTime;
    else
        return TimeUtils::Instance().GetTime() - levelStartedTime;
}