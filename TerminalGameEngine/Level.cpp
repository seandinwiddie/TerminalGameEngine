#include "Level.h"

#include "TimeHelper.h"
#include "InputUtils.h"
#include "Simulation.h"

double Level:: GetLevelTime() const
{
    if (IsGameOver())
        return gameOverTime - levelStartedTime;
    else
        return TimeHelper::Instance().GetTime() - levelStartedTime;
}

void Level::LoadInSimulation()
{
    isTerminated = false;
    gameOverTime = -1;
    levelStartedTime = TimeHelper::Instance().GetTime();
    hasCalledOnPostGameOverPauseEnded = false;
}

bool Level::IsPostGameOverPauseEnded() const
{
    return
        gameOverTime > 0 &&
        TimeHelper::Instance().GetTime() - gameOverTime > ShowGameOverScreenDelay() &&
        hasCalledOnPostGameOverPauseEnded == false;
}

bool Level::CanPlayerPressKeyToRestartGame() const
{
    return  
        TimeHelper::Instance().GetTime() - gameOverTime > 
        ShowGameOverScreenDelay() + SECONDS_PLAYER_MUST_WAIT_BEFORE_RESTARTING_PRESSING_ANY_KEY;
}

void Level::OnGameOver()
{
    if (IsGameOver())
        return;

    gameOverTime = TimeHelper::Instance().GetTime();
}

void Level::Update()
{
    if (gameOverTime < 0)
        return;

    if (IsPostGameOverPauseEnded())
        OnPostGameOverPauseEnded();
    else if (CanPlayerPressKeyToRestartGame() && InputUtils::IsAnyKeyPressed())
        Terminate();
}