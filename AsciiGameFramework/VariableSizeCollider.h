#pragma once
#include "CollidingObject.h"

class VariableSizeCollider : public CollidingObject
{
    //---------------------------------------------------------- Methods
public:
    VariableSizeCollider
    (
        const int xPos,
        const int yPos,
        const uint sizeX,
        const uint sizeY,
        const char modelChar
    ) : CollidingObject(xPos, yPos)
    {
        model = CreteModelUsingChar(modelChar, sizeX, sizeY);
    }
};