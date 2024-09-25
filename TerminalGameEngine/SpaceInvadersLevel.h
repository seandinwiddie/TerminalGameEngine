#pragma once
#include "Level.h"

class SpaceInvadersLevel : public Level
{
//------------------------------------------------------------------- Methods
public:
    virtual int GetWorldSizeX() const override { return 90; }
    virtual int GetWorldSizeY() const override { return 50; }
    virtual int GetScreenPadding() const override { return 0; }

    virtual void LoadInSimulation() override;
    virtual void NotifyGameOver() override;

protected:
    virtual void Update()override;
    virtual double ShowGameOverScreenDelay() const { return 1.5; }
    virtual void OnPostGameOverDelayEnded() override;
    void ShowGameOverScreen();
};