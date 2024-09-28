#pragma once
#include "GameObject.h"

class SpaceInvadersLevel;

class PlayerTank : public GameObject
{
//---------------------------------------------------------- Settings
public:
    static double constexpr MOVE_SPEED = 24;
    static double constexpr PROJECTILE_SPEED = 32;
    static double constexpr SHOTS_DELAY = 0.5;
    static size_t const MAX_HEALTH = 3;
//---------------------------------------------------------- Fields
public:
    Event<size_t> OnDamageTaken;

private:
    static const Model MODEL;
    SpaceInvadersLevel* level;
    double lastTimeShot = -1;
    size_t health = MAX_HEALTH;

//---------------------------------------------------------- Methods
public:
    PlayerTank(int xPos, int yPos, SpaceInvadersLevel* level) : GameObject(xPos, yPos), level(level) {};

    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::GREEN; }
    virtual void InitModel() { SetModel(MODEL); }

    void HandleMovement();
    void HandleShooting();
    void TakeDamage();
    size_t GetHealth() { return health; }

protected:
    virtual void Update() override;
};