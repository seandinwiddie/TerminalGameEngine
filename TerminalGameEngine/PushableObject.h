#pragma once
#include "GameObject.h"

class PushableObject : public GameObject
{
//---------------------------------------------------------- Methods
public:

    PushableObject(int xPos, int yPos);

    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 8; }
    virtual int GetColor() const { return Terminal::BLUE; }

protected:
    virtual void OnCollisionExit(Direction collisionDirection) override {}
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDirection) override;
};