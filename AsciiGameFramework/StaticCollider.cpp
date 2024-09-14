#include "StaticCollider.h"

StaticCollider::StaticCollider
(
    const int xPos, 
    const int yPos, 
    const int sizeX,
    const int sizeY,
    const unsigned char modelChar
) : VariableSizeCollider(xPos, yPos, sizeX, sizeY, modelChar)
{
    canMove = false;
}