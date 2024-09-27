#pragma once
#include "Config.h"
#include "Level.h"
#include <string>

class EndlessRunnerLevel : public Level
{
//---------------------------------------------------------- Settings
private:
    const string BACKGROUND_FILE_NAME = "Backgrounds/endlessRunnerBackground.txt";
    int shownTime = -1;

//---------------------------------------------------------- Methods
public:
    virtual int GetWorldSizeX() const override { return 90; }
    virtual int GetWorldSizeY() const override { return 23; }
    virtual int GetScreenPadding() const override { return 4; }
    virtual const string& GetBackgroundFileName()const override { return BACKGROUND_FILE_NAME; }

    virtual void LoadInSimulation() override;
    virtual void NotifyGameOver() override;

protected:
    virtual void Update()override;
    virtual double ShowGameOverScreenDelay() const { return 1.5; }
    virtual void OnPostGameOverDelayEnded() override;
    virtual string GetPersistenceFilePath() { return "Persistence/obstaclesLevel.txt"; }
    virtual string GetGameOverWindowPath() { return "endlessRunnerGameOverWindow.txt"; }
    virtual void ShowGameOverScreen(int score, int bestScore);
};