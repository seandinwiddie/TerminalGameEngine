#include "AutomaticDoor.h"


void AutomaticDoor::Update()
{
    VariableSizeCollider::Update();
    if (IsOpen())
    {
        if (GetPosY() < startingPosY + GetModelHeight())
            Move(Direction::up, MOVE_SPEED);
    }
    else
    {
        if (GetPosY() > startingPosY)
            Move(Direction::down, MOVE_SPEED);
    }
}

AutomaticDoor::AutomaticDoor
(
    int xPos,
    int yPos,
    size_t sizeX,
    size_t sizeY,
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