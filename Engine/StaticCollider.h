#pragma once
#include "Config.h"
#include "VariableSizeCollider.h"

namespace Engine
{
    class StaticCollider : public VariableSizeCollider
    {
        //---------------------------------------------------------- Methods
    public:
        StaticCollider
        (
            int xPos,
            int yPos,
            size_t sizeX,
            size_t sizeY,
            char modelChar
        );

        virtual bool CanExitScreenSpace() const override { return true; }
        virtual double GetGravityScale() const override { return 0; }
    };
}