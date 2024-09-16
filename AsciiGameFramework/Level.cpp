#include "Level.h"

#include "TimeUtils.h"
#include "InputUtils.h"

double Level:: GetLevelTime() const
{
    if (IsGameOver())
        return gameOverTime - levelStartedTime;
    else
        return TimeUtils::Instance().GetTime() - levelStartedTime;
}

void Level::Load()
{
    isTerminated = false;
    gameOverTime = -1;
    levelStartedTime = TimeUtils::Instance().GetTime();
    hasCalledOnGameOverDelayEnded = false;
}

bool Level::IsPostGameOverDelayEnded() const
{
    return
        gameOverTime > 0 &&
        TimeUtils::Instance().GetTime() - gameOverTime > ShowGameOverScreenDelay() &&
        hasCalledOnGameOverDelayEnded == false;
}

bool Level::CanPlayerPressKeyToRestartGame() const
{
    return  
        TimeUtils::Instance().GetTime() - gameOverTime > 
        ShowGameOverScreenDelay() + SECONDS_PLAYER_MUST_WAIT_BEFORE_RESTARTING_PRESSING_ANY_KEY;
}

void Level::OnGameOver()
{
    if (IsGameOver())
        return;

    gameOverTime = TimeUtils::Instance().GetTime();
}

void Level::Update()
{
    if (gameOverTime < 0)
        return;

    if (IsPostGameOverDelayEnded())
    {
        OnGameOverDelayEnded();
        hasCalledOnGameOverDelayEnded = true;
    }
    else if (CanPlayerPressKeyToRestartGame() && InputUtils::IsAnyKeyPressed())
    {
        Terminate();
    }
}