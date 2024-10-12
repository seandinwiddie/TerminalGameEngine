#pragma once

#include "Level.h"

class GameLoop
{
//---------------------------------------------------------- Methods
public:
    GameLoop();
private:
    std::unique_ptr<Level> ShowLevelSelection();
    bool LoopSimulation(Level* level);
};