#pragma once
#include "GameObject.h"
#include "Event.h"

class PressurePlate : public GameObject
{
//---------------------------------------------------------- Fields
public:
    Event<> OnPress;
    Event<> OnRelease;

private:
    Model pressedModel;
    Model unpressedModel;

//---------------------------------------------------------- Methods
public:
    PressurePlate(int xPos, int yPos);

    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::CYAN; }

protected:
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDirection) override;
    virtual void OnCollisionExit(Direction collisionDirection) override;
    virtual void InitModel() override { SetModel(unpressedModel); }
};