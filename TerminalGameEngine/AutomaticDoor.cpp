#include "AutomaticDoor.h"


void AutomaticDoor::Update()
{
    VariableSizeCollider::Update();
    if (IsOpen())
    {
        if (GetPosY() < startingPosY + GetModelHeight())
            Move(Direction::up, moveSpeed);
    }
    else
    {
        if (GetPosY() > startingPosY)
            Move(Direction::down, moveSpeed);
    }
}

AutomaticDoor::AutomaticDoor
(
    int xPos,
    int yPos,
    size_t sizeX,
    size_t sizeY,
    char modelChar,
    double moveSpeed
) : VariableSizeCollider(xPos, yPos, sizeX, sizeY, modelChar), moveSpeed(moveSpeed)
{
    startingPosY = yPos;
}

void AutomaticDoor::RemoveEnergySource()
{ 
    if(energySourcesCounter > 0)
        --energySourcesCounter; 
}