#pragma once
#include "Level.h";
#include <string>

using string = std::string;

class ObstaclesLevel : public Level
{
private:

    const unsigned int WORLD_SIZE_X = 90;
    const unsigned int WORLD_SIZE_Y = 24;
    const unsigned int SCREEN_PADDING = 4;
    const std::vector<string> BACKGROUND_FILES = { "background1.txt", "background2.txt" };
    const string PERSISTENCE_FILE_NAME = "ObstaclesLevelPersistence.txt";

public:
    virtual void Load() override;
    virtual void OnGameOver() override;

private:
    virtual void OnGameOverDelayEnded() override;
    void ShowGameOverScreen(int score, int bestScore);
    virtual double ShowGameOverScreenDelay()const { return 1; }
};