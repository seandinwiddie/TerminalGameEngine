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
    Simulation::Instance().LoadLevel(this);
    isTerminated = false;
    gameOverTime = -1;
    levelStartedTime = TimeHelper::Instance().GetTime();
    hasCalledOnGameOverDelayEnded = false;
}

bool Level::IsPostGameOverDelayEnded() const
{
    return
        gameOverTime > 0 &&
        TimeHelper::Instance().GetTime() - gameOverTime > ShowGameOverScreenDelay() &&
        hasCalledOnGameOverDelayEnded == false;
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