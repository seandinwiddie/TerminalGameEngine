#pragma once
#include "Level.h";

class ObstaclesLevel : public Level
{
private:

    const unsigned int WORLD_SIZE_X = 90;
    const unsigned int WORLD_SIZE_Y = 24;
    const unsigned int SCREEN_PADDING = 4;
    constexpr static float ALLOW_PRESSING_KEY_TO_RESTART_GAME_AFTER_SECONDS = 1.5;
    constexpr static float SHOW_GAMEOVER_SCREEN_AFTER_SECONDS = 1;

public:
    virtual void Load() override
    {
        levelStartedTime = 0;
        gameOverTime = -1;
        const std::vector<string> BACKGROUND_FILES = { "background1.txt", "background2.txt" };

        Simulation& simulation = Simulation::Instance();
        simulation.Reset(this, WORLD_SIZE_X, WORLD_SIZE_Y, SCREEN_PADDING, true, BACKGROUND_FILES);
        //------------------------------- bunny setup
        Bunny* bunny = new Bunny(9, simulation.GetScreenPadding() + 5, this);
        Simulation::Instance().TryAddGameObject(bunny);

        //------------------------------- floor setup
        StaticCollider* floor = new StaticCollider(0, simulation.GetScreenPadding(), simulation.GetWorldSizeX(), 1, ' ');
        simulation.TryAddGameObject(floor);

        //------------------------------- spawner setup
        int spawnerPosX = WORLD_SIZE_X - SCREEN_PADDING;
        int spawnerPosY = SCREEN_PADDING + 1;

        std::vector<float> minSpawnDelays
        {
            0.9,
            0.4,
            0.28,
            0.25,
            0.22,
            0.22
        };
        std::vector<float> maxSpawnDelays
        {
            1,
            0.6,
            0.43,
            0.4,
            0.32,
            0.22
        };
        std::vector<float> moveSpeeds
        {
            1,
            2,
            4,
            5,
            6,
            6
        };

        float increaseIntensityEverySeconds = 10;
        float stopSpawningWhenPhaseChangesDuration = 1;

        std::vector<int> ySpawnPoints = { 5,9,13 };

        ObstaclesSpawner* spawner = new ObstaclesSpawner
        (
            spawnerPosX,
            spawnerPosY,
            minSpawnDelays,
            maxSpawnDelays,
            moveSpeeds,
            increaseIntensityEverySeconds,
            stopSpawningWhenPhaseChangesDuration,
            ySpawnPoints
        );

        simulation.TryAddGameObject(spawner);
        AudioManager::Instance().PlayRandomMusic();
    }

    virtual void OnGameOver() override
    {
        AudioManager::Instance().StopMusic();
        AudioManager::Instance().PlayFx("gameover.wav");
        gameOverTime = TimeUtils::Instance().GetTime();
    }

    

private:
    virtual void Update()override
    {
        if (gameOverTime > 0)
        {
            if (IsShowGameoverDelayExpired() && Simulation::Instance().IsShowingGameOverScreen() == false)
            {
                int bestScore = Persistence::LoadBestScore();
                int score = GetLevelTime();

                Simulation::Instance().ShowGameOverScreen(score, bestScore);

                if (score > bestScore)
                    Persistence::SaveBestScore(score);
            }
            else if (CanPlayerPressKeyToRestartGame() && InputUtils::IsAnyKeyPressed())
            {
                Simulation::Instance().Terminate();
            }
        }
    }

    bool IsShowGameoverDelayExpired() const
    {
        return gameOverTime > 0 && TimeUtils::Instance().GetTime() - gameOverTime > SHOW_GAMEOVER_SCREEN_AFTER_SECONDS;
    }

    bool CanPlayerPressKeyToRestartGame() const
    {
        return  TimeUtils::Instance().GetTime() - gameOverTime > SHOW_GAMEOVER_SCREEN_AFTER_SECONDS + ALLOW_PRESSING_KEY_TO_RESTART_GAME_AFTER_SECONDS;
    }

};