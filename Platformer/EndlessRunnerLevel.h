#pragma once
#include "Config.h"
#include "Level.h"
#include <string>
#include <array>

class EndlessRunnerLevel : public Level
{
//---------------------------------------------------------- Settings
private:
    static const size_t MUSIC_FILES_COUNT = 3;
    static const std::array<string, MUSIC_FILES_COUNT> MUSIC_FILES;
    int shownTime = -1;

//---------------------------------------------------------- Methods
public:
    virtual int GetWorldSizeX() const override { return 90; }
    virtual int GetWorldSizeY() const override { return 23; }
    virtual int GetScreenPadding() const override { return 4; }
    virtual const string GetBackgroundFileName()const override { return "Resources/Backgrounds/EndlessRunner.txt"; }

    virtual void LoadInSimulation() override;

protected:
    virtual void Update()override;
    virtual double ShowGameOverScreenDelay() const { return 1.5; }
    virtual void OnPostGameOverDelayEnded() override;
    virtual string GetPersistenceFilePath() { return "Resources/Persistence/EndlessRunner.txt"; }
    virtual string GetGameOverWindowPath() { return "Resources/GameOverWindows/EndlessRunner.txt"; }
    virtual void ShowGameOverScreen(int score, int bestScore);
    virtual void OnGameOver() override;

private:
    void PlayRandomMusic();
};