#pragma once
#include "VariableSizeCollider.h"

class PongBar : public VariableSizeCollider
{
//---------------------------------------------------------- Fields
private:
    double moveSpeed;
    bool isBottomBar;
    double deflectBallFactor;

public:
//---------------------------------------------------------- Methods

public:
    PongBar
    (
        int xPos,
        int yPos,
        size_t sizeX,
        size_t sizeY,
        char modelChar,
        double moveSpeed,
        double deflectBallFactor,
        bool isBottomBar
    );

    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::CYAN; }
    
    double GetDeflectBallFactor() { return deflectBallFactor; }

protected:
    virtual void OnCollisionEnter(uset<GameObject*>collidingObjects, Direction collisionDir) override {}
    virtual void OnCollisionExit(Direction endingCollisionDir) override {}
    virtual void Update() override;
};