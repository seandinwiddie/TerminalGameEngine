#pragma once
#include "VariableSizeCollider.h"

class PongBar : public VariableSizeCollider
{
//---------------------------------------------------------- Fields
private:
    float moveSpeed;
    bool isLeftBar;
public:
//---------------------------------------------------------- Methods

public:
    PongBar
    (
        int xPos,
        int yPos,
        uint sizeX,
        uint sizeY,
        char modelChar,
        float moveSpeed,
        bool isLeftBar
    ) : VariableSizeCollider(xPos, yPos, sizeX, sizeY, modelChar), moveSpeed(moveSpeed), isLeftBar(isLeftBar){ }

    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return TerminalUtils::CYAN; }

protected:
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) override {}
    virtual void OnCollisionExit(Direction collisionDirection) override {}

private:
    virtual void Update() override;
};