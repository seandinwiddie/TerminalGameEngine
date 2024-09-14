#include "Config.h"
#include "ObstaclesSpawner.h"
#include "Bunny.h"
#include "Obstacle.h"
#include "Simulation.h"
#include "PushableObject.h"
#include "PressurePlate.h"
#include "AutomaticDoor.h"
#include "AudioManager.h"  
#include "StaticCollider.h"
#include "LevelEndFlag.h"

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

void SpawnPushableObject()
{
    PushableObject* pushableObj1 = new PushableObject(30, WORLD_SIZE_Y_TEST_ROOM - 2);
    Simulation::Instance().TryAddGameObject(pushableObj1);
}

enum Mode {GameMode, TestMode};

void SetupTestRoom()
{
    Simulation& simulation = Simulation::Instance();
 
    //------------------------------- bunny setup
    Bunny* bunny = new Bunny(4, 16);
    Simulation::Instance().TryAddGameObject(bunny);

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
    pressurePlate1->OnPress.Subscribe(SpawnPushableObject);
    simulation.TryAddGameObject(pressurePlate1);

    //------------------------------- pressure plate 2
    PressurePlate* pressurePlate2 = new PressurePlate(36, 4);
    pressurePlate2->OnPress.Subscribe([automaticDoor]() { automaticDoor->SetOpen(); });
    pressurePlate2->OnRelease.Subscribe([automaticDoor]() { automaticDoor->SetClosed(); });
    simulation.TryAddGameObject(pressurePlate2);
}

void SetupGame()
{
    Simulation& simulation = Simulation::Instance();
    //------------------------------- bunny setup
    Bunny* bunny = new Bunny(9, simulation.GetScreenPadding()+5);
    Simulation::Instance().TryAddGameObject(bunny);

    //------------------------------- floor setup
    StaticCollider* floor = new StaticCollider(0, simulation.GetScreenPadding(), simulation.GetWorldSizeX(), 1, ' ');
    simulation.TryAddGameObject(floor);

    //------------------------------- spawner setup
    int spawnerPosX = WORLD_SIZE_X_GAME - SCREEN_PADDING;
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



int main()
{
    system("COLOR 0A");
    Simulation& simulation = Simulation::Instance();

    Mode mode;
    std::cout << "Press:" << std::endl << "1 -> play game" << std::endl << "2 -> enter test room"<< std::endl;
    while (true)
    {
        if (InputUtils::IsPressing1())
        {
            mode = Mode::GameMode;
            break;
        }
        if (InputUtils::IsPressing2())
        {
            mode = Mode::TestMode;
            break;
        }
    }

    while (true)
    {
        //setup mode
        switch (mode)
        {
        case Mode::GameMode:
            //todo also pass music tracks here
            simulation.Reset(WORLD_SIZE_X_GAME, WORLD_SIZE_Y_GAME, SCREEN_PADDING, true ,GAME_BACKGROUND_FILES);
            SetupGame();
            break;
        case Mode::TestMode:
            simulation.Reset(WORLD_SIZE_X_TEST_ROOM, WORLD_SIZE_Y_TEST_ROOM, SCREEN_PADDING, false, {});
            SetupTestRoom();
            break;
        }
        
        //step simulation until it ends
        while (simulation.HasTerminated() == false)
            simulation.Step();
    }

    return 0;
}

