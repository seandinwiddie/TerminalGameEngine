#pragma once
#include "GameObject.h"

class Level;

class LevelEndFlag : public GameObject
{
private:
    static const Model flagModel;
    Level* level;

public:
    LevelEndFlag(Level* level, int xPos, int yPos);
    virtual int GetColor() const { return Terminal::GREEN; }

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDir);
    virtual void InitModel() { SetModel(flagModel); }
};