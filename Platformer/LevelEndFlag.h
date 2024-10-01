#pragma once
#include "Collider.h"
#include "Event.h"

class Level;

class LevelEndFlag : public Collider
{
//---------------------------------------------------------- Fieldds

public:
    Event<> OnTouchBunny;

private:
    static const Model flagModel;
    Level* level;

//---------------------------------------------------------- Methods
public:
    LevelEndFlag(Level* level, int xPos, int yPos);
    virtual int GetColor() const { return Terminal::GREEN; }

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
    virtual void OnCollisionEnter(Collider* other, Direction collisionDir);
    virtual void InitModel() { SetModel(flagModel); }
};