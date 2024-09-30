#pragma once

class Level;

class GameLoop
{
//---------------------------------------------------------- Methods
public:
    GameLoop();
private:
    Level* ShowLevelSelection();
    bool LoopSimulation(Level* level);
};