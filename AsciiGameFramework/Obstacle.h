#pragma once

//#include <iostream>
//#include <windows.h>
//#include <stdlib.h>
//#include <conio.h>

#include "MovingStraightObject.h"

class Obstacle : public MovingStraightObject
{
//---------------------------------------------------------- Fields
public:
    Obstacle(const int xPos, const int yPos, const Direction moveDir, const float moveSpeed);

//---------------------------------------------------------- Methods
public:
    virtual bool CanExitScreenSpace() const override { return true; }
    virtual float GetGravityScale() const override { return 0; }

protected:
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) override;
    virtual void OnCollisionExit(Direction collisionDirection) {}
};