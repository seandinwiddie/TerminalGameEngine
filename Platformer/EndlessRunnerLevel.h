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
        int GetWorldSizeX() const override { return 90; }
        int GetWorldSizeY() const override { return 23; }
        int GetScreenPadding() const override { return 4; }
        const char* GetBackgroundFileName()const override { return "Resources/Backgrounds/EndlessRunner.txt"; }

        void LoadInSimulation() override;

    protected:
        void Update()override;
        virtual double ShowGameOverScreenDelay() const { return 1.5; }
        void OnPostGameOverDelayEnded() override;
        virtual const char* GetPersistenceFilePath() { return "Resources/Persistence/EndlessRunner.txt"; }
        virtual const char* GetGameOverWindowPath() { return "Resources/GameOverWindows/EndlessRunner.txt"; }
        virtual void ShowGameOverScreen(int score, int bestScore);
        void OnGameOver() override;

    private:
        void PlayRandomMusic();
    };
}