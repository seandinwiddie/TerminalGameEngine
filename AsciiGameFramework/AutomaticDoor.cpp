#include "AutomaticDoor.h"


void AutomaticDoor::Update()
{
    if (IsOpen())
    {
        if (GetPosY() < startingPosY + GetModelHeight())
            MoveContinuous(Direction::up, MOVE_SPEED);
    }
    else
    {
        if (GetPosY() > startingPosY)
            MoveContinuous(Direction::down, MOVE_SPEED);
    }
}

AutomaticDoor::AutomaticDoor
(
    int xPos,
    int yPos,
    uint sizeX,
    uint sizeY,
    char modelChar
) : VariableSizeCollider(xPos, yPos, sizeX, sizeY, modelChar)
{
    startingPosY = yPos;
}

void AutomaticDoor::RemoveEnergySource()
{ 
    if(energySourcesCounter > 0)
        --energySourcesCounter; 
}