#pragma once
#include "Level.h"
#include "Config.h"

namespace PongLevelScore
{
    static uint scorePlayer1 = 0;
    static uint scorePlayer2 = 0;
}


class PongLevel : public Level
{
    //---------------------------------------------------------- Methods
public:
    virtual int GetWorldSizeX() const override { return 90; }
    virtual int GetWorldSizeY() const override { return 30; }
    virtual int GetScreenPadding() const override { return 2; }

    virtual void Load() override;

    virtual void OnGameOverDelayEnded() override { Terminate(); }

    void IncreaseP1Score() { ++ PongLevelScore::scorePlayer1; }
    void IncreaseP2Score() { ++PongLevelScore::scorePlayer2; }

    /*virtual void OnGameOver() override;

private:
    virtual void OnGameOverDelayEnded() override;
    void ShowGameOverScreen(int score, int bestScore);*/
};