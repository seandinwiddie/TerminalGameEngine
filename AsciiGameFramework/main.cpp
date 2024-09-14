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
#include "LevelLoadUtils.h"

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

using namespace LevelLoadUtils;

int main()
{
    system("COLOR 0A");
    Simulation& simulation = Simulation::Instance();
    Level level = ShowLevelSelection();
    
    while (true)
    {
        LoadLevel(level);
        
        //step simulation until it ends
        while (simulation.HasTerminated() == false)
            simulation.Step();
    }

    return 0;
}

