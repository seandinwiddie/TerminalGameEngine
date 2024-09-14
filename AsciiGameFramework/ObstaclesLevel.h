#pragma once
#include "ILevel.h";

class ObstaclesLevel : public ILevel
{
public:
    virtual void Load() override
    {
        const unsigned int WORLD_SIZE_X = 90;
        const unsigned int WORLD_SIZE_Y = 24;
        const unsigned int SCREEN_PADDING = 4;

        const std::vector<string> BACKGROUND_FILES = { "background1.txt", "background2.txt" };


        Simulation& simulation = Simulation::Instance();
        simulation.Reset(WORLD_SIZE_X, WORLD_SIZE_Y, SCREEN_PADDING, true, BACKGROUND_FILES);
        //------------------------------- bunny setup
        Bunny* bunny = new Bunny(9, simulation.GetScreenPadding() + 5);
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

        Simulation::Instance().OnGameOver.Subscribe(OnGameOver);
        Simulation::Instance().OnGameStart.Subscribe(OnGameStart);
    }

    static void OnGameOver()
    {
        AudioManager::Instance().StopMusic();
        AudioManager::Instance().PlayFx("gameover.wav");
    }

    static void OnGameStart()
    {
        AudioManager::Instance().PlayRandomMusic();
    }
};