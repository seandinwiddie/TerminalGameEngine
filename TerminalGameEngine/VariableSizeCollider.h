#pragma once
#include "GameObject.h"

class VariableSizeCollider : public GameObject
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
    ) : GameObject(xPos, yPos)
    {
        SetModel(CreteModelUsingChar(modelChar, sizeX, sizeY));
    }
};