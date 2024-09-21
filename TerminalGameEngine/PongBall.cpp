#include "PongBall.h"
#include "Simulation.h"

void PongBall::OnCollisionEnter(CollidingObject* other, Direction collisionDirection)
{
    if (GetPosX() == level->GetWorldSizeX() - level->GetScreenPadding() - 1)
    {
        level->OnGameOver();
        Simulation::Instance().RemoveObject(this);
        return;
    }
        

    if (GetPosX() == level->GetScreenPadding())
    {
        level->OnGameOver();
        Simulation::Instance().RemoveObject(this);
        return;
    }
        

    if (collisionDirection == Direction::up || collisionDirection == Direction::down)
        ySpeed = -ySpeed;
    else
        xSpeed = -xSpeed;
}

void PongBall::Update()
{
    CollidingObject::Update();

    if (ySpeed > 0)
        Move(Direction::up, ySpeed);
    else if (ySpeed < 0)
        Move(Direction::down, ySpeed);

    if (xSpeed > 0)
        Move(Direction::right, xSpeed);
    else if (xSpeed < 0)
        Move(Direction::left, xSpeed);
}