#pragma once

#include "Config.h"
#include "Simulation.h"
#include "Bunny.h"
#include "StaticCollider.h"
#include "LevelEndFlag.h"
#include "AutomaticDoor.h"
#include "PressurePlate.h"
#include "ObstaclesSpawner.h"
#include "PushableObject.h"
#include "Simulation.h"

namespace LevelLoadUtils
{
    static enum Level { Obstacles, Puzzle };

    static void LoadObstaclesLevel()
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

        Simulation::Instance().OnGameOver.Subscribe
        (
            []()
            {
                AudioManager::Instance().StopMusic();
                AudioManager::Instance().PlayFx("gameover.wav");
            }
        );
        Simulation::Instance().OnGameStart.Subscribe([]() { AudioManager::Instance().PlayRandomMusic(); });
    }

    static void LoadPuzzleGame()
    {
        const unsigned int WORLD_SIZE_X = 120;
        const unsigned int WORLD_SIZE_Y = 30;
        const unsigned int SCREEN_PADDING = 4;
       

        Simulation& simulation = Simulation::Instance();
        simulation.Reset(WORLD_SIZE_X, WORLD_SIZE_Y, SCREEN_PADDING, false, {});
        //------------------------------- bunny setup
        Bunny* bunny = new Bunny(4, 16);
        simulation.TryAddGameObject(bunny);

        //------------------------------- left platform
        StaticCollider* platform = new StaticCollider(24, 11, 12, 1, '#');
        simulation.TryAddGameObject(platform);

        //------------------------------- right flag platform
        StaticCollider* doorRightPlatform = new StaticCollider(63, 14, 16, 1, '#');
        simulation.TryAddGameObject(doorRightPlatform);

        LevelEndFlag* flag = new LevelEndFlag(65, 15);
        simulation.TryAddGameObject(flag);

        //------------------------------- automatic door
        AutomaticDoor* automaticDoor = new AutomaticDoor(60, 4, 2, 6, '|');
        simulation.TryAddGameObject(automaticDoor);

        //------------------------------- automatic door container
        StaticCollider* automaticDoorTopRight = new StaticCollider(62, 10, 1, 18, '#');
        simulation.TryAddGameObject(automaticDoorTopRight);

        StaticCollider* automaticDoorTopLeft = new StaticCollider(59, 10, 1, 18, '#');
        simulation.TryAddGameObject(automaticDoorTopLeft);

        //------------------------------- pressure plate 1
        PressurePlate* pressurePlate1 = new PressurePlate(15, 4);
        pressurePlate1->OnPress.Subscribe
        (
            [&simulation]()
            {
                PushableObject* pushableObj1 = new PushableObject(30, WORLD_SIZE_Y - 2);
                simulation.TryAddGameObject(pushableObj1);
            }
        );
        simulation.TryAddGameObject(pressurePlate1);

        //------------------------------- pressure plate 2
        PressurePlate* pressurePlate2 = new PressurePlate(36, 4);
        pressurePlate2->OnPress.Subscribe([automaticDoor]() { automaticDoor->SetOpen(); });
        pressurePlate2->OnRelease.Subscribe([automaticDoor]() { automaticDoor->SetClosed(); });
        simulation.TryAddGameObject(pressurePlate2);
    }
    
    static void LoadLevel(Level level)
    {
        switch (level)
        {
        case Level::Obstacles:
            LoadObstaclesLevel();
            break;
        case Level::Puzzle:
            LoadPuzzleGame();
            break;
        }
    }

    static Level ShowLevelSelection()
    {
        std::cout << "Press:" << std::endl << "1 -> play game" << std::endl << "2 -> enter test room" << std::endl;

        while (true)
        {
            if (InputUtils::IsPressing1())
            {
                return Level::Obstacles;
                break;
            }
            if (InputUtils::IsPressing2())
            {
               return  Level::Puzzle;
                break;
            }
        }
    }
}