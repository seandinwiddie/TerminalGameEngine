#include "Level.h"

double Level:: GetLevelTime() const
{
    if (IsGameOver())
        return gameOverTime - levelStartedTime;
    else
        return TimeUtils::Instance().GetTime() - levelStartedTime;
}

void Level::Load()
{
    gameOverTime = -1;
    levelStartedTime = TimeUtils::Instance().GetTime();
    isShowingGameOverScreen = false;
}

bool Level::IsShowGameoverDelayExpired() const
{
    return gameOverTime > 0 && TimeUtils::Instance().GetTime() - gameOverTime > SHOW_GAMEOVER_SCREEN_AFTER_SECONDS;
}

bool Level::CanPlayerPressKeyToRestartGame() const
{
    return  TimeUtils::Instance().GetTime() - gameOverTime > SHOW_GAMEOVER_SCREEN_AFTER_SECONDS + ALLOW_PRESSING_KEY_TO_RESTART_GAME_AFTER_SECONDS;
}

void Level::OnGameOver()
{
    if (IsGameOver())
        return;

    gameOverTime = TimeUtils::Instance().GetTime();
}