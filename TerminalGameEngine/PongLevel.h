#pragma once
#include "Level.h"
#include "Config.h"

class PongLevel : public Level
{
//---------------------------------------------------------- Methods
private:
    static uint scorePlayer1;
    static uint scorePlayer2;
//---------------------------------------------------------- Methods
public:
    virtual int GetWorldSizeX() const override { return 50; }
    virtual int GetWorldSizeY() const override { return 35; }
    virtual int GetScreenPadding() const override { return 2; }

    virtual void LoadInSimulation() override;

    virtual void OnGameOverDelayEnded() override { Terminate(); }

    void IncreaseP1Score();
    void IncreaseP2Score();

private:
    void RefreshHeader();
};