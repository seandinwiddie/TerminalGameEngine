#include "StaticCollider.h"

StaticCollider::StaticCollider
(
    int xPos, 
    int yPos, 
    uint sizeX,
    uint sizeY,
    char modelChar
) : VariableSizeCollider(xPos, yPos, sizeX, sizeY, modelChar)
{
    canMove = false;
}