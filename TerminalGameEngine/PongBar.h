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
        uint sizeX,
        uint sizeY,
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
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDirection) override {}
    virtual void OnCollisionExit(Direction collisionDirection) override {}
    virtual void Update() override;
};