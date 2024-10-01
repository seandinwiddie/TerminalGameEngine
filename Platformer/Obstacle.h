#pragma once

#include "MovingStraightObject.h"

class Obstacle : public MovingStraightObject
{
private:
    static Model model;
//---------------------------------------------------------- Methods
public:
    using MovingStraightObject::MovingStraightObject;

    virtual bool CanExitScreenSpace() const override { return true; }
    virtual double GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::RED; }

protected:
    virtual void OnCollisionEnter(Collider* other, Direction collisionDir) override;
    virtual void InitModel();
};