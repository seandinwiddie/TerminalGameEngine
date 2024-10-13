#pragma once
#include "Collider.h"
#include "Event.h"

namespace Platformer
{
    using Direction = Engine::Direction;

    class PressurePlate : public Engine::Collider
    {
        //---------------------------------------------------------- Fields
    public:
        Event<> OnPress;
        Event<> OnRelease;

    private:
        Engine::Model pressedModel;
        Engine::Model unpressedModel;

        //---------------------------------------------------------- Methods
    public:
        PressurePlate(int xPos, int yPos, size_t width);

        virtual bool CanExitScreenSpace() const override { return false; }
        virtual double GetGravityScale() const override { return 0; }
        virtual int GetColor() const { return Engine::Terminal::CYAN; }

    protected:
        virtual void OnCollisionEnter(Collider* other, Direction collisionDir) override;
        virtual void OnCollisionExit(Direction endingCollisionDir) override;
        virtual void InitModel() override { SetModel(unpressedModel); }
    };
}