#pragma once
#include "Simulation.h"
#include "CollidingObject.h"

class PushableObject : public CollidingObject
{
//---------------------------------------------------------- Methods
public:

    PushableObject(int xPos, int yPos);

    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 1; }

protected:
    virtual void OnCollisionExit(Direction collisionDirection) override {}
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) override;
};