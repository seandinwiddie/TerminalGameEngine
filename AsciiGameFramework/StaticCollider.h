#pragma once

#include "Config.h"
#include "VariableSizeCollider.h"

class StaticCollider : public VariableSizeCollider
{    
//---------------------------------------------------------- Methods
public:
    StaticCollider
    (
        const int xPos,
        const int yPos,
        const uint sizeX,
        const uint sizeY,
        const char modelChar
    );

    virtual bool CanExitScreenSpace() const override { return true; }
    virtual float GetGravityScale() const override { return 0; }

protected:
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) override {}
    virtual void OnCollisionExit(Direction collisionDirection) override {}
};