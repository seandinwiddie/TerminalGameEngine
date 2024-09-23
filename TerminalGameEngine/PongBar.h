#pragma once
#include "VariableSizeCollider.h"

class PongBar : public VariableSizeCollider
{
//---------------------------------------------------------- Fields
private:
    float moveSpeed;
    bool isBottomBar;
    float deflectBallFactor;

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
        float deflectBallFactor,
        bool isBottomBar
    );

    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::CYAN; }
    
    float GetDeflectBallFactor() { return deflectBallFactor; }

protected:
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDirection) override {}
    virtual void OnCollisionExit(Direction collisionDirection) override {}
    virtual void Update() override;
    virtual void InitModel() override { SetModel({ {static_cast<char>(219)} }); }
};