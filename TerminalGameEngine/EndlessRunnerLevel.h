#pragma once

#include "Config.h"
#include "Level.h";
#include <string>

class EndlessRunnerLevel : public Level
{
//---------------------------------------------------------- Settings
private:
    const string PERSISTENCE_FILE_NAME = "ObstaclesLevelPersistence.txt";
    const string BACKGROUND_FILE_NAME = "endlessRunnerBackground.txt";

    int shownTime = -1;

//---------------------------------------------------------- Methods
public:
    virtual int GetWorldSizeX() const override { return 90; }
    virtual int GetWorldSizeY() const override { return 23; }
    virtual int GetScreenPadding() const override { return 4; }
    virtual string GetBackgroundFileName() override { return BACKGROUND_FILE_NAME; }

    virtual void LoadInSimulation() override;
    virtual void OnGameOver() override;

protected:
    virtual void Update()override;

private:
    virtual void OnPostGameOverDelayEnded() override;
    void ShowGameOverScreen(int score, int bestScore);
};