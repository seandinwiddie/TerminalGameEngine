#pragma once
#include "GameObject.h"

class Level;

class LevelEndFlag : public GameObject
{
private:
    static const std::vector<std::vector<char>> flagModel;
    Level* level;

public:
    LevelEndFlag(Level* level, int xPos, int yPos);
    virtual int GetColor() const { return Terminal::GREEN; }

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 0; }
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDirection);
    virtual void OnCollisionExit(Direction collisionDirection){ }
    virtual void InitModel() { SetModel(flagModel); }
};