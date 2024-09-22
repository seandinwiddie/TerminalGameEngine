#pragma once
#include "CollidingObject.h"	
#include "PongLevel.h"
#include "RandomUtils.h"

class PongBar;

class PongBall : public CollidingObject
{
private:
    PongLevel* level;
    float xSpeed;
    float ySpeed;
    bool iSFirstLaunch;

public:
    PongBall(PongLevel* level, int xPos, int yPos, float xSpeed) : 
        CollidingObject(xPos, yPos), level(level), xSpeed(xSpeed)
    {
        SetModel({{static_cast<char>(219)}});

        ySpeed = 0;
        iSFirstLaunch = true;

        if (RandomUtils::GetRandomInt(0, 1) == 1)
            this->xSpeed = -xSpeed;
    }

    virtual int GetColor() const { return Terminal::GREEN; }

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 0; }
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection);
    virtual void OnCollisionExit(Direction collisionDirection) {}
    virtual void Update() override;

private:
    void HandleBarCollision(PongBar* collidingBar);
};