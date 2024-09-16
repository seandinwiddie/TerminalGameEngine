#pragma once
#include "CollidingObject.h"
#include "Event.h"

class PressurePlate : public CollidingObject
{
//---------------------------------------------------------- Fields
public:
    Event<> OnPress;
    Event<> OnRelease;

private:
    std::vector<std::vector<char>> pressedModel;
    std::vector<std::vector<char>> unpressedModel;

//---------------------------------------------------------- Methods
public:
    PressurePlate(const int xPos, const int yPos);

    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 0; }

protected:
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) override;
    virtual void OnCollisionExit(Direction collisionDirection) override;
};