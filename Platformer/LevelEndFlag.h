#pragma once
#include "Collider.h"
#include "Event.h"

namespace Engine {class Level;}

namespace Platformer
{
    //class Engine::Level;
    template<typename T> using shared_ptr = std::shared_ptr<T>;
    using Direction = Engine::Direction;
    using Level = Engine::Level;

    class LevelEndFlag : public Engine::Collider
    {
        //---------------------------------------------------------- Fieldds

    public:
        Event<> OnTouchBunny;

    private:
        static const Engine::Model flagModel;
        Engine::Level* level;

        //---------------------------------------------------------- Methods
    public:
        LevelEndFlag(Level* level, int xPos, int yPos);
        virtual int GetColor() const { return Engine::Terminal::GREEN; }

    protected:
        virtual bool CanExitScreenSpace() const override { return false; }
        virtual double GetGravityScale() const override { return 0; }
        virtual void OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir);
        virtual void InitModel() { SetModel(flagModel); }
    };
}