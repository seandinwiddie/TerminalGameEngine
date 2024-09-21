#pragma once
#include "CollidingObject.h"	
#include "Level.h"

class PongBar;

class PongBall : public CollidingObject
{
private:
    Level* level;
    float xSpeed;
    float ySpeed;

public:
    PongBall(Level* level, int xPos, int yPos, float xSpeed) : 
        CollidingObject(xPos, yPos), level(level), xSpeed(xSpeed)
    {
        ySpeed = 0;
        model = { {static_cast<char>(219)}};
    }

    virtual int GetColor() const { return TerminalUtils::GREEN; }

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 0; }
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection);
    virtual void OnCollisionExit(Direction collisionDirection) {}
    virtual void Update() override;

private:
    void HandleBarCollision(PongBar* collidingBar);
};