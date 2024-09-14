#pragma once
#include "ILevel.h";

class PuzzleLevel : public ILevel
{
public:

    static const unsigned int WORLD_SIZE_X = 120;
    static const unsigned int WORLD_SIZE_Y = 30;
    static const unsigned int SCREEN_PADDING = 4;

	virtual void Load() override
	{
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
        pressurePlate1->OnPress.Subscribe(SpawnPushableBlock);
        simulation.TryAddGameObject(pressurePlate1);

        //------------------------------- pressure plate 2
        PressurePlate* pressurePlate2 = new PressurePlate(36, 4);
        pressurePlate2->OnPress.Subscribe([automaticDoor]() { automaticDoor->SetOpen(); });
        pressurePlate2->OnRelease.Subscribe([automaticDoor]() { automaticDoor->SetClosed(); });
        simulation.TryAddGameObject(pressurePlate2);
	}

    static void SpawnPushableBlock()
    {
        PushableObject* pushableObj1 = new PushableObject(30, WORLD_SIZE_Y - 2);
        Simulation::Instance().TryAddGameObject(pushableObj1);
    }
};