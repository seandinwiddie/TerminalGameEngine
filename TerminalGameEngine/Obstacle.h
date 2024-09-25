#pragma once

#include "MovingStraightObject.h"

class Obstacle : public MovingStraightObject
{
private:
    Model model = CreteModelUsingChar(-37, size_t(4), size_t(2));
//---------------------------------------------------------- Methods
public:
    Obstacle(int xPos, int yPos, Direction moveDir, double moveSpeed);

    virtual bool CanExitScreenSpace() const override { return true; }
    virtual double GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::RED; }

protected:
    virtual void OnCollisionEnter(uset<GameObject*>collidingObjects, Direction collisionDir) override;
    virtual void OnCollisionExit(Direction endingCollisionDir) {}
    virtual void InitModel(){ SetModel(model); }
};