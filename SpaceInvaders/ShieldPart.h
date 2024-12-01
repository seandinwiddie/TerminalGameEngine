#pragma once
#include "StaticCollider.h"

namespace SpaceInvaders
{
    template<typename T> using shared_ptr = std::shared_ptr<T>;
    using Direction = Engine::Direction;
    using Model = Engine::Model;

    class ShieldPart : public Engine::Collider
    {
        //---------------------------------------------------------- Fields
    private:
        Model model = CreteModelUsingChar('=', 1, 1);

        //---------------------------------------------------------- Methods
    public:
        using Collider::Collider;

    protected:
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        int GetColor() const override { return Engine::Terminal::GREEN; }
        void InitModel() override { SetModel(model); }
        void OnCollisionEnter(shared_ptr<Collider>other, Direction collisionDir)override;
    };
}