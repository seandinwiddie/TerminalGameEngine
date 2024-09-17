#include "StaticCollider.h"

StaticCollider::StaticCollider
(
    const int xPos, 
    const int yPos, 
    const uint sizeX,
    const uint sizeY,
    const char modelChar
) : VariableSizeCollider(xPos, yPos, sizeX, sizeY, modelChar)
{
    canMove = false;
}