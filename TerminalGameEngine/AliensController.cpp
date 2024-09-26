#pragma once
#include "AliensController.h"
#include "Alien.h"
#include "Level.h"
#include "TimeHelper.h"
#include "SpaceInvadersLevel.h"
#include "DebugManager.h"
#include <cassert>

double AliensController::GetMoveDelay()
{ 
	return
		BEGINNING_MOVE_DELAY - 

		//waves progress reduces timer (wave reaching min delay reached -> max reduction)
		level->GetWaveNumber() / WAVE_REACHING_MIN_DELAY * MAX_DELAY_REDUCTION_WAVES -
		//5 / WAVE_REACHING_MIN_DELAY * MAX_DELAY_REDUCTION_WAVES -

		//killing aliens reduces timer (all enemies destroyed = max timer reduction)
		MAX_DELAY_REDUCTION_ELIMINATING_ALIENS * GetDestroyedAliensCount() / GetStartingAliensCount();
}

AliensController::AliensController(SpaceInvadersLevel* level, int aliensCountX, int aliensCountY) : level(level)
{
	aliensCount = aliensCountX * aliensCountY;

	aliens.resize(aliensCountY);
	for (int y = 0; y < aliensCountY; ++y)
		aliens[y].resize(aliensCountX);
}

void AliensController::Update()
{
	double time = TimeHelper::Instance().GetTime();
	if (time - lastTimeMoved > GetMoveDelay())
	{
		DebugManager::Instance().PrintGenericLog(std::to_string(GetMoveDelay()));
		if (isTimeToMoveAliensDown)
		{
			MoveAliens(Direction::down, 9999);
			isTimeToMoveAliensDown = false;
		}
		else
			MoveAliens(xMoveDirection, 9999);
	}
}

void AliensController::RegisterAlien(Alien* alien, int xPos, int yPos)
{
	assert(alien != nullptr);
	assert(yPos < GetAliensGridHeight());
	assert(xPos < GetAliensGridWidth());

	aliens[yPos][xPos] = alien;

	alien->OnMove.Subscribe
	(
		[this](GameObject* alien, Direction dir) { OnAlienMovedCallback(alien, dir); }
	);

	alien->OnDestroy.Subscribe
	(
		[this](int xIndex, int yIndex) { OnAlienDestroyedCallback(xIndex, yIndex); }
	);
}

void AliensController::OnAlienMovedCallback(GameObject* alien, Direction moveDirection)
{
	if (moveDirection == xMoveDirection)
	{
		int alienXPos = alien->GetPosX();
		if (alienXPos == level->GetScreenPadding() || alienXPos == level->GetScreenMaxX() - alien->GetModelWidth())
			OnAliensReachMargin();
	}
}

void AliensController::MoveAliens(Direction dir, double speed)
{
	for (int y = 0; y < GetAliensGridHeight(); ++y)
		for (int x = 0; x < GetAliensGridWidth(); ++x)
			if (aliens[y][x] != nullptr)
				aliens[y][x]->TryMove(dir, speed);

	lastTimeMoved = TimeHelper::Instance().GetTime();
}

void AliensController::OnAliensReachMargin()
{
	xMoveDirection = GetInverseDirection(xMoveDirection);
	isTimeToMoveAliensDown = true;
}

void AliensController::OnAlienDestroyedCallback(int xIndex, int yIndex)
{
	aliens[yIndex][xIndex] = nullptr;
	--aliensCount;
}