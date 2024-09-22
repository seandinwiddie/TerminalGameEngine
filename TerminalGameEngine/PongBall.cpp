#include "PongBall.h"
#include "PongBar.h"
#include "Simulation.h"

void PongBall::OnCollisionEnter(CollidingObject* other, Direction collisionDirection)
{
    if (GetPosX() == level->GetWorldSizeX() - level->GetScreenPadding() - 1)
    {
        level->IncreaseP1Score();
        level->OnGameOver();
        Simulation::Instance().RemoveObject(this);
        return;
    }
        

    if (GetPosX() == level->GetScreenPadding())
    {
        level->IncreaseP2Score();
        level->OnGameOver();
        Simulation::Instance().RemoveObject(this);
        return;
    }
        

    if (collisionDirection == Direction::up || collisionDirection == Direction::down)
        ySpeed = -ySpeed;
    else
    {
        xSpeed = -xSpeed;
        PongBar* otherBar = dynamic_cast<PongBar*>(other);
        if (otherBar != nullptr)
            HandleBarCollision(otherBar);
    } 
}

void PongBall::HandleBarCollision(PongBar* collidingBar)
{
    int otherHeight = collidingBar->GetModelHeight();

    int otherMidY = (collidingBar->GetMaxPosY() + collidingBar->GetPosY()) / 2;
    int distanceFromMidPoint = GetPosY() - otherMidY;

    if (distanceFromMidPoint <= 0)
        distanceFromMidPoint -= 1;

    ySpeed = distanceFromMidPoint * collidingBar->GetDeflectBallFactor();
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