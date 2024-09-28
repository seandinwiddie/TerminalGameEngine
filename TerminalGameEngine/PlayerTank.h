#pragma once
#include "GameObject.h"

class SpaceInvadersLevel;

class PlayerTank : public GameObject
{
//---------------------------------------------------------- Settings
private:
    double const MOVE_SPEED = 24;
    double const PROJECTILES_MOVE_SPEED = 32;
    double const SHOTS_DELAY = 0.5;

//---------------------------------------------------------- Fields
private:
    static const Model MODEL;
    SpaceInvadersLevel* level;
    double lastTimeShot = -1;

//---------------------------------------------------------- Methods
public:
    PlayerTank(int xPos, int yPos, SpaceInvadersLevel* level) : GameObject(xPos, yPos), level(level) {};

    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::GREEN; }
    virtual void InitModel() { SetModel(MODEL); }

    void HandleMovement();
    void HandleShooting();

protected:
    virtual void Update() override;
};