#pragma once
#include "Collider.h"	
#include "Event.h"

namespace Pong
{
    class PongBar;
    class PongLevel;

    template<typename T> using shared_ptr = std::shared_ptr<T>;
    using Model = Engine::Model;
    using Direction = Engine::Direction;

    class PongBall : public Engine::Collider
    {
        //---------------------------------------------------------- Fields
    public:
        Event<> OnGoal;
    private:
        PongLevel* level;
        double ySpeed;
        double xSpeed;
        bool iSFirstLaunch;
        static const Model MODEL;

        //---------------------------------------------------------- Methods
    public:
        PongBall(PongLevel* level, int xPos, int yPos, double ySpeed);
        int GetColor() const override { return Engine::Terminal::GREEN; }

    protected:
        bool CanExitScreenSpace() const override { return false; }
        double GetGravityScale() const override { return 0; }
        void OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir) override;
        void Update() override;
        void InitModel() override { SetModel(MODEL); }

    private:
        void HandleBarCollision(shared_ptr<PongBar> collidingBar);
    };
}

