#pragma once
#include "Level.h";

class ObstaclesLevel : public Level
{
private:

    const unsigned int WORLD_SIZE_X = 90;
    const unsigned int WORLD_SIZE_Y = 24;
    const unsigned int SCREEN_PADDING = 4;
    const std::vector<string> BACKGROUND_FILES = { "background1.txt", "background2.txt" };
    const string PERSISTENCE_FILE_NAME = "ObstaclesLevelPersistence.txt";

public:
    virtual void Load() override
    {
        Level::Load();

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
        if (IsGameOver())
            return;

        Level::OnGameOver();

        AudioManager::Instance().StopMusic();
        AudioManager::Instance().PlayFx("gameover.wav");
    }

private:
    virtual void Update()override
    {
        if (gameOverTime < 0)
            return;

        if (IsShowGameoverDelayExpired() && isShowingGameOverScreen == false)
        {
            int bestScore = Persistence::LoadBestScore(PERSISTENCE_FILE_NAME);
            int score = GetLevelTime();

            if (score > bestScore)
                Persistence::SaveBestScore(PERSISTENCE_FILE_NAME, score);

            Simulation::Instance().ShowGameOverScreen(score, bestScore);

            isShowingGameOverScreen = true;
        }
        else if (CanPlayerPressKeyToRestartGame() && InputUtils::IsAnyKeyPressed())
        {
            Simulation::Instance().Terminate();
        }
    }
};