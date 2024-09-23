#pragma once
#include "GameObject.h"	
#include "PongLevel.h"
#include "RandomUtils.h"

class PongBar;

class PongBall : public GameObject
{
private:
    PongLevel* level;
    float ySpeed;
    float xSpeed;
    bool iSFirstLaunch;

public:
    PongBall(PongLevel* level, int xPos, int yPos, float ySpeed);
    virtual int GetColor() const { return Terminal::GREEN; }

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 0; }
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDirection);
    virtual void OnCollisionExit(Direction collisionDirection) {}
    virtual void Update() override;
    virtual void InitModel() override { SetModel({ {static_cast<char>(219)} }); }

private:
    void HandleBarCollision(PongBar* collidingBar);
};