#pragma once
#include "Level.h"

class PongLevel : public Level
{
    //---------------------------------------------------------- Settings
private:
    const string PERSISTENCE_FILE_NAME = "ObstaclesLevelPersistence.txt";

    //---------------------------------------------------------- Methods
public:
    virtual int GetWorldSizeX() const override { return 90; }
    virtual int GetWorldSizeY() const override { return 30; }
    virtual int GetScreenPadding() const override { return 2; }

    virtual void Load() override;
    /*virtual void OnGameOver() override;

private:
    virtual void OnGameOverDelayEnded() override;
    void ShowGameOverScreen(int score, int bestScore);*/
};