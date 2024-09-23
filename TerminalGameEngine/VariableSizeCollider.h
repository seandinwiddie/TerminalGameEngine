#pragma once
#include "GameObject.h"

class VariableSizeCollider : public GameObject
{
//---------------------------------------------------------- Fields
    char modelChar;
    size_t modelSizeX;
    size_t modelSizeY;
//---------------------------------------------------------- Methods
public:
    VariableSizeCollider
    (
        int xPos,
        int yPos,
        size_t modelSizeX,
        size_t modelSizeY,
        char modelChar
    ) : GameObject(xPos, yPos), modelSizeX(modelSizeX), modelSizeY(modelSizeY), modelChar(modelChar){ }

protected:
    virtual void InitModel() override { SetModel( CreteModelUsingChar(modelChar, modelSizeX, modelSizeY) ); }
};