#include "AutomaticDoor.h"


void AutomaticDoor::Update()
{
    if (IsOpen())
    {
        if (GetPosY() < startingY + GetModelHeight())
            Move(Direction::up, MOVE_SPEED);
    }
    else
    {
        if (GetPosY() > startingY)
            Move(Direction::down, MOVE_SPEED);
    }
}

AutomaticDoor::AutomaticDoor
(
    const int xPos,
    const int yPos,
    const int sizeX,
    const int sizeY,
    const unsigned char modelChar
) :VariableSizeCollider(xPos, yPos, sizeX, sizeY, modelChar)
{
    startingY = yPos;
}