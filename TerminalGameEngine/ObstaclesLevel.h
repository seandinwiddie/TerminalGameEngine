#pragma once

#include "Config.h"
#include "Level.h";
#include <string>

class ObstaclesLevel : public Level
{
//---------------------------------------------------------- Settings
private:
    const uint WORLD_SIZE_X = 90;
    const uint WORLD_SIZE_Y = 24;
    const uint SCREEN_PADDING = 4;
    const std::vector<string> BACKGROUND_FILES = {"background1.txt", "background2.txt"};
    const string PERSISTENCE_FILE_NAME = "ObstaclesLevelPersistence.txt";

//---------------------------------------------------------- Methods
public:
    virtual void Load() override;
    virtual void OnGameOver() override;

private:
    virtual void OnGameOverDelayEnded() override;
    void ShowGameOverScreen(int score, int bestScore);
};