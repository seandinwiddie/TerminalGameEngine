#pragma once
#include "VariableSizeCollider.h"

namespace Pong
{
    class PongBar : public Engine::VariableSizeCollider
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
        virtual int GetColor() const { return Engine::Terminal::CYAN; }

        double GetDeflectBallFactor() { return deflectBallFactor; }

    protected:
        virtual void Update() override;
    };
}