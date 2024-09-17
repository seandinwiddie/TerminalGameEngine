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
    StaticCollider* flagPlatform = new StaticCollider(63, 15, 16, 1, '#');
    simulation.TryAddGameObject(flagPlatform);

    //------------------------------- right flag
    LevelEndFlag* flag = new LevelEndFlag(this, 70, 16);
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

    //------------------------------- open door pressure plate left
    PressurePlate* openDoorPressurePlateLeft = new PressurePlate(36, 4);
    openDoorPressurePlateLeft->OnPress.Subscribe([automaticDoor]() { automaticDoor->AddEnergySource(); });
    openDoorPressurePlateLeft->OnRelease.Subscribe([automaticDoor]() { automaticDoor->RemoveEnergySource(); });
    simulation.TryAddGameObject(openDoorPressurePlateLeft);

    //------------------------------- open door pressure plate right
    PressurePlate* openDoorPressurePlateRight = new PressurePlate(86, 4);
    openDoorPressurePlateRight->OnPress.Subscribe([automaticDoor]() { automaticDoor->AddEnergySource(); });
    openDoorPressurePlateRight->OnRelease.Subscribe([automaticDoor]() { automaticDoor->RemoveEnergySource(); });
    simulation.TryAddGameObject(openDoorPressurePlateRight);
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