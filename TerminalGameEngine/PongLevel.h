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
    virtual int GetWorldSizeX() const override { return 90; }
    virtual int GetWorldSizeY() const override { return 30; }
    virtual int GetScreenPadding() const override { return 2; }

    virtual void LoadInSimulation() override;

    virtual void OnGameOverDelayEnded() override { Terminate(); }

    void IncreaseP1Score() { ++ scorePlayer1; }
    void IncreaseP2Score() { ++ scorePlayer2; }

protected:
    virtual void Update() override;
};