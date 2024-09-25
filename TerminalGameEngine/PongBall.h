#pragma once
#include "GameObject.h"	
#include "PongLevel.h"
#include "RandomUtils.h"

class PongBar;

class PongBall : public GameObject
{
//---------------------------------------------------------- Fields
private:
    PongLevel* level;
    double ySpeed;
    double xSpeed;
    bool iSFirstLaunch;
    Model model = {{-37}};

//---------------------------------------------------------- Methods
public:
    PongBall(PongLevel* level, int xPos, int yPos, double ySpeed);
    virtual int GetColor() const { return Terminal::GREEN; }

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDir);
    virtual void Update() override;
    virtual void InitModel() override { SetModel(model); }

private:
    void HandleBarCollision(PongBar* collidingBar);
};