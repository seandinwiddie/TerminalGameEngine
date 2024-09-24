#pragma once

#include "Config.h"
#include "VariableSizeCollider.h"

class StaticCollider : public VariableSizeCollider
{    
//---------------------------------------------------------- Methods
public:
    StaticCollider
    (
        int xPos,
        int yPos,
        size_t sizeX,
        size_t sizeY,
        char modelChar
    );

    virtual bool CanExitScreenSpace() const override { return true; }
    virtual double GetGravityScale() const override { return 0; }

protected:
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDirection) override {}
    virtual void OnCollisionExit(Direction endingCollisionDirection) override {}
};