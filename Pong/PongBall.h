#pragma once
#include "Collider.h"	
#include "Event.h"

class PongBar;
class PongLevel;

class PongBall : public Collider
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
    virtual int GetColor() const { return Terminal::GREEN; }

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
    virtual void OnCollisionEnter(Collider* other, Direction collisionDir);
    virtual void Update() override;
    virtual void InitModel() override { SetModel(MODEL); }

private:
    void HandleBarCollision(PongBar* collidingBar);
};