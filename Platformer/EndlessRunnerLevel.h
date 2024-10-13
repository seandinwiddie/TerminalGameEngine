#pragma once
#include "Config.h"
#include "Level.h"
#include <string>
#include <array>

namespace Platformer
{
    class EndlessRunnerLevel : public Engine::Level
    {
        //---------------------------------------------------------- Settings
    private:
        static const size_t MUSIC_FILES_COUNT = 3;
        static const std::array<const char*, MUSIC_FILES_COUNT> MUSIC_FILES;
        int shownTime = -1;

        //---------------------------------------------------------- Methods
    public:
        virtual int GetWorldSizeX() const override { return 90; }
        virtual int GetWorldSizeY() const override { return 23; }
        virtual int GetScreenPadding() const override { return 4; }
        virtual const char* GetBackgroundFileName()const override { return "Resources/Backgrounds/EndlessRunner.txt"; }

        virtual void LoadInSimulation() override;

    protected:
        virtual void Update()override;
        virtual double ShowGameOverScreenDelay() const { return 1.5; }
        virtual void OnPostGameOverDelayEnded() override;
        virtual const char* GetPersistenceFilePath() { return "Resources/Persistence/EndlessRunner.txt"; }
        virtual const char* GetGameOverWindowPath() { return "Resources/GameOverWindows/EndlessRunner.txt"; }
        virtual void ShowGameOverScreen(int score, int bestScore);
        virtual void OnGameOver() override;

    private:
        void PlayRandomMusic();
    };
}