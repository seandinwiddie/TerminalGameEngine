#pragma once
#include "GameObject.h"	
#include "PongLevel.h"
#include "RandomUtils.h"

class PongBar;

class PongBall : public GameObject
{
private:
    PongLevel* level;
    double ySpeed;
    double xSpeed;
    bool iSFirstLaunch;

public:
    PongBall(PongLevel* level, int xPos, int yPos, double ySpeed);
    virtual int GetColor() const { return Terminal::GREEN; }

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDirection);
    virtual void OnCollisionExit(Direction endingCollisionDirection) {}
    virtual void Update() override;
    virtual void InitModel() override { SetModel({ {-37} }); }

private:
    void HandleBarCollision(PongBar* collidingBar);
};