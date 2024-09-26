#include "PongBall.h"
#include "PongBar.h"
#include "Simulation.h"
#include "AudioManager.h"

PongBall::PongBall(PongLevel* level, int xPos, int yPos, double ySpeed) 
    :
    GameObject(xPos, yPos), 
    level(level),
    ySpeed(ySpeed)
{
    xSpeed = 0;
    iSFirstLaunch = true;

    if (RandomUtils::GetRandomInt(0, 1) == 1)
        this->ySpeed = -ySpeed;
}

void PongBall::OnCollisionEnter(GameObject* other, Direction collisionDir)
{
    iSFirstLaunch = false;

    if (GetPosY() == level->GetWorldSizeY() - level->GetScreenPadding() - 1)
    {
        level->IncreaseP1Score();
        level->NotifyGameOver();
        return;
    }
        

    if (GetPosY() == level->GetScreenPadding())
    {
        level->IncreaseP2Score();
        level->NotifyGameOver();
        return;
    }

    AudioManager::Instance().PlayFx("Pong/ballHit1.wav",0.02);

    if (collisionDir == Direction::up || collisionDir == Direction::down)
    {
        ySpeed = -ySpeed;

        PongBar* colliderBar = dynamic_cast<PongBar*>(other);
        if (colliderBar != nullptr)
            HandleBarCollision(colliderBar);
    }
    else
    {
        xSpeed = -xSpeed;
    }
}

void PongBall::HandleBarCollision(PongBar* collidingBar)
{
    int otherMidX = (collidingBar->GetMaxPosX() + collidingBar->GetPosX()) / 2;
    int distanceFromMidPoint = GetPosX() - otherMidX;

    if (distanceFromMidPoint <= 0)
        distanceFromMidPoint -= 1;
    
    int originalSign = distanceFromMidPoint > 0 ? 1 : -1;
    xSpeed = std::pow(std::abs(distanceFromMidPoint), collidingBar->GetDeflectBallFactor());
    xSpeed *= originalSign;
}

void PongBall::Update()
{
    if (level->IsGameOver())
        return;

    GameObject::Update();

    if (xSpeed > 0)
        TryMove(Direction::right, xSpeed);
    else if (xSpeed < 0)
        TryMove(Direction::left, xSpeed);

    if (ySpeed > 0)
        TryMove(Direction::up, ySpeed);
    else if (ySpeed < 0)
        TryMove(Direction::down, ySpeed);
}