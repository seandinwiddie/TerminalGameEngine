#include "PlayerTank.h"
#include "Simulation.h"
#include "InputUtils.h"
#include "PlayerProjectile.h"
#include "TimeHelper.h"
#include "Level.h"
#include "AudioManager.h"
#include "SpaceInvadersLevel.h"

using namespace InputUtils;

const Model PlayerTank::MODEL =
{
    {' ', '_', '^', '_', ' '},
    {'/', '_', '_', '_', '\\'},
};

void PlayerTank::Update()
{
    if (Simulation::Instance().GetActiveLevel()->IsGameOver())
        return;

    HandleMovement();
    HandleShooting();
}

void PlayerTank::HandleMovement()
{
    if (IsKeyPressed(Key::A) || IsKeyPressed(Key::ARROW_LEFT))
        TryMove(Direction::left, MOVE_SPEED);
    else if (IsKeyPressed(Key::D) || IsKeyPressed(Key::ARROW_RIGHT))
        TryMove(Direction::right, MOVE_SPEED);
}

void PlayerTank::HandleShooting()
{
    if (level->IsLoadingWave())
        return;

    if (IsKeyPressed(Key::SPACE))
    {
        double time = TimeHelper::Instance().GetTime();

#if CHEAT_SPACEINV_FAST_FIRE
        if(time-lastTimeShot > 0.08)
            lastTimeShot = -99;
#endif

        if (time - lastTimeShot > SHOTS_DELAY)
        {
            lastTimeShot = TimeHelper::Instance().GetTime();
            PlayerProjectile* projectile = new PlayerProjectile(GetMidPosX(), GetMaxPosY() + 1, Direction::up, PROJECTILE_SPEED);
            Simulation::Instance().TryAddEntity(projectile);
            AudioManager::Instance().PlayFx("SpaceInv/shot1.wav");
        }
    }
}

void PlayerTank::TakeDamage()
{
#if !CHEAT_SPACEINV_INVINCIBILITY
    health--;
    OnDamageTaken.Notify(health);

    if(health > 0)
        AudioManager::Instance().PlayFx("SpaceInv/damageTaken.wav");
#endif
}