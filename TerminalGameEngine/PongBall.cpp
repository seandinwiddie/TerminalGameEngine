#include "PongBall.h"
#include "PongBar.h"
#include "Simulation.h"

void PongBall::OnCollisionEnter(CollidingObject* other, Direction collisionDirection)
{
    iSFirstLaunch = false;

    if (GetPosY() == level->GetWorldSizeY() - level->GetScreenPadding() - 1)
    {
        level->IncreaseP1Score();
        level->OnGameOver();
        return;
    }
        

    if (GetPosY() == level->GetScreenPadding())
    {
        level->IncreaseP2Score();
        level->OnGameOver();
        return;
    }

    if (collisionDirection == Direction::up || collisionDirection == Direction::down)
    {
        ySpeed = -ySpeed;
        PongBar* otherBar = dynamic_cast<PongBar*>(other);
        if (otherBar != nullptr)
            HandleBarCollision(otherBar);
    } 
}

void PongBall::HandleBarCollision(PongBar* collidingBar)
{
    int otherWidth = collidingBar->GetModelWidth();

    int otherMidX = (collidingBar->GetMaxPosX() + collidingBar->GetPosX()) / 2;
    int distanceFromMidPoint = GetPosX() - otherMidX;

    if (distanceFromMidPoint <= 0)
        distanceFromMidPoint -= 1;

    xSpeed = distanceFromMidPoint * 8 * collidingBar->GetDeflectBallFactor();
}

void PongBall::Update()
{
    if (level->IsGameOver())
        return;

    CollidingObject::Update();

    if (collidingDirections[static_cast<int>(Direction::left)] == true || collidingDirections[static_cast<int>(Direction::right)])
        xSpeed = -xSpeed;

    if (xSpeed > 0)
        Move(Direction::right, xSpeed);
    else if (xSpeed < 0)
        Move(Direction::left, xSpeed);

    if (ySpeed > 0)
        Move(Direction::up, ySpeed);
    else if (ySpeed < 0)
        Move(Direction::down, ySpeed);
}