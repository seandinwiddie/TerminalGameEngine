#include "PuzzleLevel.h"

#include "Bunny.h"
#include "StaticCollider.h"
#include "LevelEndFlag.h"
#include "AutomaticDoor.h"
#include "PressurePlate.h"
#include "PushableObject.h"
#include "AudioManager.h"


void PuzzleLevel::Load()
{
    Level::Load();

    Simulation& simulation = Simulation::Instance();
    simulation.Reset(this, WORLD_SIZE_X, WORLD_SIZE_Y, SCREEN_PADDING, false, {});
    //------------------------------- bunny setup
    Bunny* bunny = new Bunny(6, 4, this);
    simulation.TryAddGameObject(bunny);

    //------------------------------- left platform
    StaticCollider* platform = new StaticCollider(24, 11, 12, 1, '#');
    simulation.TryAddGameObject(platform);

    //------------------------------- right flag platform
    StaticCollider* doorRightPlatform = new StaticCollider(63, 14, 16, 1, '#');
    simulation.TryAddGameObject(doorRightPlatform);

    LevelEndFlag* flag = new LevelEndFlag(this, 70, 15);
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
        []()
        {
            PushableObject* pushableObj1 = new PushableObject(30, WORLD_SIZE_Y - 2);
            Simulation::Instance().TryAddGameObject(pushableObj1);
        }
    );
    simulation.TryAddGameObject(pressurePlate1);

    //------------------------------- pressure plate 2
    PressurePlate* pressurePlate2 = new PressurePlate(36, 4);
    pressurePlate2->OnPress.Subscribe([automaticDoor]() { automaticDoor->SetOpen(); });
    pressurePlate2->OnRelease.Subscribe([automaticDoor]() { automaticDoor->SetClosed(); });
    simulation.TryAddGameObject(pressurePlate2);
}

void PuzzleLevel::OnGameOver()
{
    Level::OnGameOver();
    AudioManager::Instance().PlayFx("levelWon.wav");
}

void PuzzleLevel::OnGameOverDelayEnded()
{
    Terminate();
}