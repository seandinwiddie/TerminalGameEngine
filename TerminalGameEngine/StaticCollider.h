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
        uint sizeX,
        uint sizeY,
        char modelChar
    );

    virtual bool CanExitScreenSpace() const override { return true; }
    virtual float GetGravityScale() const override { return 0; }

protected:
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) override {}
    virtual void OnCollisionExit(Direction collisionDirection) override {}
};