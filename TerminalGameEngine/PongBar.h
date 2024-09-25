#pragma once
#include "VariableSizeCollider.h"

class PongBar : public VariableSizeCollider
{
//---------------------------------------------------------- Fields
private:
    double moveSpeed;
    bool isBottomBar;
    double deflectBallFactor;

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
    virtual void Update() override;
};