#pragma once
#include "Level.h"

namespace Platformer
{
    class CollisionsTestLevel : public Engine::Level
    {
        //---------------------------------------------------------- Methods
    public:
        virtual int GetWorldSizeX() const override { return 100; }
        virtual int GetWorldSizeY() const override { return 30; }
        virtual int GetScreenPadding() const override { return 4; }
        virtual double ShowGameOverScreenDelay()const { return 0; }

        virtual void LoadInSimulation() override;
    };
}