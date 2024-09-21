#pragma once
#include "PuzzleLevel.h"

#include "Bunny.h"
#include "StaticCollider.h"
#include "LevelEndFlag.h"
#include "AutomaticDoor.h"
#include "PressurePlate.h"
#include "AudioManager.h"
#include "PushableObject.h"


void PuzzleLevel::Load()
{
    Level::Load();
    Simulation& simulation = Simulation::Instance();
    //------------------------------- bunny setup
    Bunny* bunny = new Bunny(6, 4, this);
    simulation.TryAddObject(bunny);

    //------------------------------- left platform
    StaticCollider* platform = new StaticCollider(24, 11, 12, 1, '#');
    simulation.TryAddObject(platform);

    //------------------------------- right flag platform
    StaticCollider* flagPlatform = new StaticCollider(63, 15, 16, 1, '#');
    simulation.TryAddObject(flagPlatform);

    //------------------------------- right flag
    LevelEndFlag* flag = new LevelEndFlag(this, 70, 16);
    simulation.TryAddObject(flag);

    //------------------------------- automatic door
    AutomaticDoor* automaticDoor = new AutomaticDoor(60, 4, 2, 6, '|');
    simulation.TryAddObject(automaticDoor);

    //------------------------------- automatic door container
    StaticCollider* automaticDoorTopRight = new StaticCollider(62, 10, 1, 18, '#');
    simulation.TryAddObject(automaticDoorTopRight);

    StaticCollider* automaticDoorTopLeft = new StaticCollider(59, 10, 1, 18, '#');
    simulation.TryAddObject(automaticDoorTopLeft);

    //------------------------------- pressure plate 1
    PressurePlate* pressurePlate1 = new PressurePlate(15, 4);
    pressurePlate1->OnPress.Subscribe
    (
        []()
        {
            PushableObject* pushableObj1 = new PushableObject(30, 20);
            Simulation::Instance().TryAddObject(pushableObj1);
        }
    );
    simulation.TryAddObject(pressurePlate1);

    //------------------------------- open door pressure plate left
    PressurePlate* openDoorPressurePlateLeft = new PressurePlate(36, 4);
    openDoorPressurePlateLeft->OnPress.Subscribe([automaticDoor]() { automaticDoor->AddEnergySource(); });
    openDoorPressurePlateLeft->OnRelease.Subscribe([automaticDoor]() { automaticDoor->RemoveEnergySource(); });
    simulation.TryAddObject(openDoorPressurePlateLeft);

    //------------------------------- open door pressure plate right
    PressurePlate* openDoorPressurePlateRight = new PressurePlate(86, 4);
    openDoorPressurePlateRight->OnPress.Subscribe([automaticDoor]() { automaticDoor->AddEnergySource(); });
    openDoorPressurePlateRight->OnRelease.Subscribe([automaticDoor]() { automaticDoor->RemoveEnergySource(); });
    simulation.TryAddObject(openDoorPressurePlateRight);
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