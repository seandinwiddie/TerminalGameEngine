#pragma once
#include "Level.h";

class PuzzleLevel : public Level
{
public:

    static const unsigned int WORLD_SIZE_X = 120;
    static const unsigned int WORLD_SIZE_Y = 30;
    static const unsigned int SCREEN_PADDING = 4;

    virtual void Load() override;

    static void SpawnPushableBlock();
    virtual void OnGameOver() override;
};