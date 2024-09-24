#pragma once

#include "MovingStraightObject.h"

class Obstacle : public MovingStraightObject
{
//---------------------------------------------------------- Methods
public:
    Obstacle(int xPos, int yPos, Direction moveDir, double moveSpeed);

    virtual bool CanExitScreenSpace() const override { return true; }
    virtual double GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::RED; }

protected:
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDirection) override;
    virtual void OnCollisionExit(Direction endingCollisionDirection) {}
    virtual void InitModel() { SetModel(CreteModelUsingChar( -37, size_t(4), size_t(2))); }
};