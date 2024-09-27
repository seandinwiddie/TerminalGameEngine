#pragma once
#include "StaticCollider.h"

class ShieldPart : public GameObject
{
//---------------------------------------------------------- Fields
private:
    Model model = CreteModelUsingChar('=', 1, 1);

//---------------------------------------------------------- Methods
public:
    using GameObject::GameObject;

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::GREEN; }
    virtual void InitModel() { SetModel(model); }
};