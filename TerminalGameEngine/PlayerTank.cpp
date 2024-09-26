#include "PlayerTank.h"
#include "Simulation.h"
#include "InputUtils.h"
#include "PlayerProjectile.h"

using namespace InputUtils;

const Model PlayerTank::MODEL =
{
    {'|', '=', '=', '=', '|'},
    {'_', '_', 'A', '_', '_'}
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
    if (IsKeyPressed(Key::SPACE))
    {
        PlayerProjectile* projectile = new PlayerProjectile(GetMidPosX(), GetMaxPosY() + 1, Direction::up, PROJECTILES_MOVE_SPEED);
        Simulation::Instance().TryAddEntity(projectile);
    }
}