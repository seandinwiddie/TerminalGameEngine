#pragma once

#include "Config.h"
#include "Level.h";
#include <string>

class EndlessRunnerLevel : public Level
{
//---------------------------------------------------------- Settings
private:
    const string PERSISTENCE_FILE_NAME = "ObstaclesLevelPersistence.txt";

//---------------------------------------------------------- Methods
public:
    virtual int GetWorldSizeX() const override { return 90; }
    virtual int GetWorldSizeY() const override { return 24; }
    virtual int GetScreenPadding() const override { return 4; }
    virtual std::vector<string> GetBackgroundFilesNames() { return { "background1.txt", "background2.txt" }; }

    virtual void Load() override;
    virtual void OnGameOver() override;

private:
    virtual void OnGameOverDelayEnded() override;
    void ShowGameOverScreen(int score, int bestScore);
};