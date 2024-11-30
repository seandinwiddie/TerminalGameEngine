#pragma once

#include "Level.h"

using Level = Engine::Level;

class GameLoop
{
    //---------------------------------------------------------- Methods
public:
    GameLoop();
private:
    std::shared_ptr<Level> ShowLevelSelection();
    bool LoopSimulation(std::shared_ptr<Level> level);
};