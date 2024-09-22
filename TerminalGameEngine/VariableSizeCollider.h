#pragma once
#include "CollidingObject.h"

class VariableSizeCollider : public CollidingObject
{
    //---------------------------------------------------------- Methods
public:
    VariableSizeCollider
    (
        int xPos,
        int yPos,
        uint sizeX,
        uint sizeY,
        char modelChar
    ) : CollidingObject(xPos, yPos)
    {
        SetModel(CreteModelUsingChar(modelChar, sizeX, sizeY));
    }
};