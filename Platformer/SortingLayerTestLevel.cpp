#include "SortingLayerTestLevel.h"
#include "Level.h"
#include "Simulation.h"
#include "Bunny.h"
#include "SortingLayerTestObject.h"

namespace Platformer
{
    void SortingLayerTestLevel::LoadInSimulation()
    {
        Level::LoadInSimulation();
        Engine::Simulation& simulation = Engine::Simulation::Instance();

        //----------------- bunny setup
        int bunnyStartingY = static_cast<int>(simulation.GetScreenPadding());
        Bunny* bunny = new Bunny(9, bunnyStartingY);
        bunny->OnObstacleHit.Subscribe([this]() { OnGameOver(); });
        simulation.TryAddEntity(bunny);

        //----------------- front object
        SortingLayerTestObject* sortingLayerTestObjFront = new SortingLayerTestObject
        (
            20,     //posx
            4,      //posy
            30,      //sizex
            5,      //sizey
            -37,     //char
            Engine::Terminal::RED,
            200     //sorting layer
        );
        simulation.TryAddEntity(sortingLayerTestObjFront);

        //----------------- back object
        SortingLayerTestObject* sortingLayerTestObjBack = new SortingLayerTestObject
        (
            60,     //posx
            4,      //posy
            30,      //sizex
            5,      //sizey
            -37,     //char
            Engine::Terminal::BLUE,
            0       //sorting layer
        );
        simulation.TryAddEntity(sortingLayerTestObjBack);
    }
}