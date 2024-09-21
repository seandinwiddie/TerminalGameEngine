#pragma once

#include "MovingStraightObject.h"

class Obstacle : public MovingStraightObject
{
//---------------------------------------------------------- Fields
public:
    Obstacle(int xPos, int yPos, Direction moveDir, float moveSpeed);

//---------------------------------------------------------- Methods
public:
    virtual bool CanExitScreenSpace() const override { return true; }
    virtual float GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return TerminalUtils::RED; }

protected:
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) override;
    virtual void OnCollisionExit(Direction collisionDirection) {}
};