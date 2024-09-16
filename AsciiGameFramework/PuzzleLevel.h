#pragma once
#include "Level.h";

class PuzzleLevel : public Level
{
//---------------------------------------------------------- Settings
private:
    static const unsigned int WORLD_SIZE_X = 120;
    static const unsigned int WORLD_SIZE_Y = 30;
    static const unsigned int SCREEN_PADDING = 4;

//---------------------------------------------------------- Methods
public:
    virtual void Load() override;
    virtual void OnGameOver() override;
    virtual void OnGameOverDelayEnded() override;
    virtual double ShowGameOverScreenDelay()const { return 1.5; }
};