#pragma once
#include "GameObject.h"

class VariableSizeCollider : public GameObject
{
//---------------------------------------------------------- Fields
    char modelChar;
    size_t modelSizeX;
    size_t modelSizeY;
    Model model;
//---------------------------------------------------------- Methods
public:
    VariableSizeCollider
    (
        int xPos,
        int yPos,
        size_t modelSizeX,
        size_t modelSizeY,
        char modelChar
    ) : 
        GameObject(xPos, yPos), 
        modelSizeX(modelSizeX), 
        modelSizeY(modelSizeY), 
        modelChar(modelChar)
    {
       model = CreteModelUsingChar(modelChar, modelSizeX, modelSizeY);
    }

protected:
    virtual void InitModel() override { SetModel(model); }
};