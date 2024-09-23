#pragma once
#include "Level.h";

class PuzzleLevel : public Level
{
//---------------------------------------------------------- Methods
public:
    virtual void LoadInSimulation() override;
    virtual void OnGameOver() override;
    virtual void OnPostGameOverDelayEnded() override;
    virtual double ShowGameOverScreenDelay() const { return 1.5; }

    virtual int GetWorldSizeX() const override { return 120; }
    virtual int GetWorldSizeY() const override { return 30; }
    virtual int GetScreenPadding() const override { return 4; }
};