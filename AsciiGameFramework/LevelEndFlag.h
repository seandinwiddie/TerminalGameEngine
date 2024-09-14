#pragma once
#include "CollidingObject.h"


class LevelEndFlag : public CollidingObject
{
private:
    static const std::vector<std::vector<unsigned char>> flagModel;

public:
    LevelEndFlag(const int x, const int y);

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 0; }
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection);
    virtual void OnCollisionExit(Direction collisionDirection){ }
};