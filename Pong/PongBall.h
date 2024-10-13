#pragma once
#include "Collider.h"	
#include "Event.h"

namespace Pong
{
    class PongBar;
    class PongLevel;

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
        virtual int GetColor() const { return Engine::Terminal::GREEN; }

    protected:
        virtual bool CanExitScreenSpace() const override { return false; }
        virtual double GetGravityScale() const override { return 0; }
        virtual void OnCollisionEnter(Collider* other, Direction collisionDir);
        virtual void Update() override;
        virtual void InitModel() override { SetModel(MODEL); }

    private:
        void HandleBarCollision(PongBar* collidingBar);
    };
}

