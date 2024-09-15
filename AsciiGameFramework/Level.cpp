#include "Level.h"

#include "TimeUtils.h"
#include "Simulation.h"
#include "ScreenManager.h"
#include "StaticCollider.h"
#include "Persistence.h"
#include "InputUtils.h"
#include "AudioManager.h"
#include "Bunny.h"
#include "ObstaclesSpawner.h"
#include "Frame.h"

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
    isGameOverDelayEnded = false;
}

bool Level::IsShowGameoverDelayExpired() const
{
    return gameOverTime > 0 && TimeUtils::Instance().GetTime() - gameOverTime > ShowGameOverScreenDelay();
}

bool Level::CanPlayerPressKeyToRestartGame() const
{
    return  TimeUtils::Instance().GetTime() - gameOverTime > ShowGameOverScreenDelay() + ALLOW_PRESSING_KEY_TO_RESTART_GAME_AFTER_SECONDS;
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

    if (IsShowGameoverDelayExpired() && isGameOverDelayEnded == false)
    {
        isGameOverDelayEnded = true;
        OnGameOverDelayEnded();
    }
    else if (CanPlayerPressKeyToRestartGame() && InputUtils::IsAnyKeyPressed())
    {
        Terminate();
    }
}