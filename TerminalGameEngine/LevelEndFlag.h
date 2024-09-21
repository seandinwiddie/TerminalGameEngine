#pragma once
#include "CollidingObject.h"

class Level;

class LevelEndFlag : public CollidingObject
{
private:
    static const std::vector<std::vector<char>> flagModel;
    Level* level;

public:
    LevelEndFlag(Level* level, int xPos, int yPos);
    virtual int GetColor() const { return TerminalUtils::YELLOW; }

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 0; }
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection);
    virtual void OnCollisionExit(Direction collisionDirection){ }
};