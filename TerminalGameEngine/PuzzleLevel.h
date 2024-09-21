#pragma once

#include "Config.h"
#include "Level.h";

class PuzzleLevel : public Level
{
//---------------------------------------------------------- Methods
public:
    virtual void Load() override;
    virtual void OnGameOver() override;
    virtual void OnGameOverDelayEnded() override;
    virtual double ShowGameOverScreenDelay() const { return 1.5; }

    virtual int GetWorldSizeX() const override { return 120; }
    virtual int GetWorldSizeY() const override { return 30; }
    virtual int GetScreenPadding() const override { return 4; }
};