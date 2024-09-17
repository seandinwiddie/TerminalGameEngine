#include "AutomaticDoor.h"


void AutomaticDoor::Update()
{
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
    const int xPos,
    const int yPos,
    const uint sizeX,
    const uint sizeY,
    const char modelChar
) : VariableSizeCollider(xPos, yPos, sizeX, sizeY, modelChar)
{
    startingPosY = yPos;
}