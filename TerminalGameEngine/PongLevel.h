#pragma once
#include "Level.h"
#include "Config.h"
#include "AudioManager.h"

class PongLevel : public Level
{
//---------------------------------------------------------- Methods
private:
    static size_t scorePlayer1;
    static size_t scorePlayer2;
//---------------------------------------------------------- Methods
public:
    virtual int GetWorldSizeX() const override { return 50; }
    virtual int GetWorldSizeY() const override { return 35; }
    virtual int GetScreenPadding() const override { return 2; }

    virtual void LoadInSimulation() override;

    void IncreaseP1Score();
    void IncreaseP2Score();

    virtual void OnGameOver() override;

protected:
    virtual void OnPostGameOverDelayEnded() override;
    virtual double ShowGameOverScreenDelay() const override { return 0.5; }

private:
    void RefreshHeader();
};