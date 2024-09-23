#pragma once

#include "MovingStraightObject.h"

class Obstacle : public MovingStraightObject
{
//---------------------------------------------------------- Methods
public:
    Obstacle(int xPos, int yPos, Direction moveDir, float moveSpeed);

    virtual bool CanExitScreenSpace() const override { return true; }
    virtual float GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::RED; }

protected:
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDirection) override;
    virtual void OnCollisionExit(Direction collisionDirection) {}
    virtual void InitModel() { SetModel(CreteModelUsingChar(219, 4, 2)); }
};