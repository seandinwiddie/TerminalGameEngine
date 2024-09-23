#pragma once
#include "GameObject.h"

class VariableSizeCollider : public GameObject
{
//---------------------------------------------------------- Fields
    char modelChar;
    uint modelSizeX;
    uint modelSizeY;
//---------------------------------------------------------- Methods
public:
    VariableSizeCollider
    (
        int xPos,
        int yPos,
        uint modelSizeX,
        uint modelSizeY,
        char modelChar
    ) : GameObject(xPos, yPos), modelSizeX(modelSizeX), modelSizeY(modelSizeY), modelChar(modelChar){ }

protected:
    virtual void InitModel() override { SetModel( CreteModelUsingChar(modelChar, modelSizeX, modelSizeY) ); }
};