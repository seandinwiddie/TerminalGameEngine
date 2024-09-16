#pragma once

#include "Config.h"
#include "Level.h";
#include <string>

using string = std::string;

class ObstaclesLevel : public Level
{
//---------------------------------------------------------- Settings
private:
    const unsigned int WORLD_SIZE_X = 90;
    const unsigned int WORLD_SIZE_Y = 24;
    const unsigned int SCREEN_PADDING = 4;
    const std::vector<string> BACKGROUND_FILES = { "background1.txt", "background2.txt" };
    const string PERSISTENCE_FILE_NAME = "ObstaclesLevelPersistence.txt";

//---------------------------------------------------------- Methods
public:
    virtual void Load() override;
    virtual void OnGameOver() override;

private:
    virtual void OnGameOverDelayEnded() override;
    void ShowGameOverScreen(const uint score, const uint bestScore);
};