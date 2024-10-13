#pragma once
#include "PuzzleLevel.h"
#include "Simulation.h"
#include "Bunny.h"
#include "StaticCollider.h"
#include "AutomaticDoor.h"
#include "PressurePlate.h"
#include "LevelEndFlag.h"
#include "AudioManager.h"
#include "PushableObject.h"

namespace Platformer
{
    using StaticCollider = Engine::StaticCollider;
    
    void PuzzleLevel::LoadInSimulation()
    {
        Level::LoadInSimulation();
        Engine::Simulation& simulation = Engine::Simulation::Instance();

        //------------ bunny
        //Bunny* bunny = new Bunny(5, 4, this);
        Bunny* bunny = new Bunny(5, 8);
        simulation.TryAddEntity(bunny);

        //------------ left platform
        StaticCollider* platform = new StaticCollider(24, 11, 12, 1, '#');
        simulation.TryAddEntity(platform);

        //------------ right flag platform
        StaticCollider* flagPlatform = new StaticCollider(63, 15, 16, 1, '#');
        simulation.TryAddEntity(flagPlatform);

        //------------ flag
        LevelEndFlag* flag = new LevelEndFlag(this, 70, 16);
        flag->OnTouchBunny.Subscribe([this]() { OnGameOver(); });
        simulation.TryAddEntity(flag);

        //------------ automatic door
        AutomaticDoor* automaticDoor = new AutomaticDoor(60, 4, 2, 6, '|', 4);
        simulation.TryAddEntity(automaticDoor);

        //------------ automatic door container
        StaticCollider* automaticDoorTopRight = new StaticCollider(62, 10, 1, 18, '#');
        simulation.TryAddEntity(automaticDoorTopRight);

        StaticCollider* automaticDoorTopLeft = new StaticCollider(59, 10, 1, 18, '#');
        simulation.TryAddEntity(automaticDoorTopLeft);

        //------------ pressure plate left
        PressurePlate* pressurePlate1 = new PressurePlate(14, 4, 8);
        pressurePlate1->OnPress.Subscribe
        (
            [this]()
            {
                PushableObject* pushableObj1 = new PushableObject(32, GetWorldSizeY() - 2);
                Engine::Simulation::Instance().TryAddEntity(pushableObj1);
            }
        );
        simulation.TryAddEntity(pressurePlate1);

        //------------ pressure plate center
        PressurePlate* openDoorPressurePlateLeft = new PressurePlate(37, 4, 8);
        openDoorPressurePlateLeft->OnPress.Subscribe([automaticDoor]() { automaticDoor->AddEnergySource(); });
        openDoorPressurePlateLeft->OnRelease.Subscribe([automaticDoor]() { automaticDoor->RemoveEnergySource(); });
        simulation.TryAddEntity(openDoorPressurePlateLeft);

        //------------ pressure plate right
        PressurePlate* openDoorPressurePlateRight = new PressurePlate(86, 4, 8);
        openDoorPressurePlateRight->OnPress.Subscribe([automaticDoor]() { automaticDoor->AddEnergySource(); });
        openDoorPressurePlateRight->OnRelease.Subscribe([automaticDoor]() { automaticDoor->RemoveEnergySource(); });
        simulation.TryAddEntity(openDoorPressurePlateRight);
    }

    void PuzzleLevel::OnGameOver()
    {
        Level::OnGameOver();
        Engine::AudioManager::Instance().PlayFx("Resources/Sounds/Platform/LevelWon.wav");
    }

    void PuzzleLevel::OnPostGameOverDelayEnded()
    {
        Level::OnPostGameOverDelayEnded();
        Terminate();
    }
}