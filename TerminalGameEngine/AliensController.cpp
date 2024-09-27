#pragma once
#include "Config.h"
#include "AliensController.h"
#include "Alien.h"
#include "Level.h"
#include "TimeHelper.h"
#include "SpaceInvadersLevel.h"
#include "DebugManager.h"
#include <cassert>

double AliensController::GetSpeedX() const
{
	return BASE_MOVE_SPEED + GetEliminatedAliensSpeedBoost() + GetWaveSpeedBoost();
}

double AliensController::GetEliminatedAliensSpeedBoost()const
{
	return static_cast<double>(GetDestroyedAliensCount()) / (GetStartingAliensCount()-1) * ALL_ALIENS_ELIMINATED_SPEED_INCREASE;
}

double AliensController::GetWaveSpeedBoost()const
{
	return level->GetWaveNumber() / MAX_SPEED_WAVE * HARDEST_WAVE_SPEED_INCREASE;
}

AliensController::AliensController(SpaceInvadersLevel* level, int aliensCountX, int aliensCountY) : level(level)
{
	aliensCount = aliensCountX * aliensCountY;

	aliensGrid.resize(aliensCountY);
	for (int y = 0; y < aliensCountY; ++y)
		aliensGrid[y].resize(aliensCountX);

	frontLine.resize(aliensCountX);

}

void AliensController::Update()
{
#if DEBUG_MODE
	string totBoost = "tot boost: " + std::to_string(GetSpeedX());
	string eliminationsBoost = " elim.boost:"+ std::to_string(GetEliminatedAliensSpeedBoost());
	string waveBoost = " wave boost:" + std::to_string(GetWaveSpeedBoost());
	string debugStr = totBoost + " | " + eliminationsBoost + " | " + waveBoost;
	DebugManager::Instance().PrintGenericLog(debugStr);
#endif

	if (isTimeToMoveAliensDown)
	{
		if (GetFrontlineMinY() - 1 == GAME_OVER_Y + level->GetScreenPadding())
			level->NotifyGameOver();

		MoveAliens(Direction::down, 9999);
		isTimeToMoveAliensDown = false;
	}
	else
		MoveAliens(xMoveDirection, GetSpeedX());
}

void AliensController::RegisterAlien(Alien* alien, int xPos, int yPos)
{
	assert(alien != nullptr);
	assert(yPos < GetAliensGridHeight());
	assert(xPos < GetAliensGridWidth());

	aliensGrid[yPos][xPos] = alien;

	if (yPos == GetAliensGridHeight()-1)
		frontLine[xPos] = alien;

	alien->OnMove.Subscribe
	(
		[this](GameObject* alien, Direction dir) { OnAlienMovedCallback(alien, dir); }
	);

	alien->OnDestroy.Subscribe
	(
		[this](GameObject* alienObj) { OnAlienDestroyedCallback(alienObj); }
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
			if (aliensGrid[y][x] != nullptr)
				aliensGrid[y][x]->TryMove(dir, speed);
}

void AliensController::OnAliensReachMargin()
{
	xMoveDirection = GetInverseDirection(xMoveDirection);
	isTimeToMoveAliensDown = true;
}

void AliensController::OnAlienDestroyedCallback(GameObject* alienObj)
{
	Alien* alien = dynamic_cast<Alien*>(alienObj);
	size_t destroyedX = alien->GetIndexInGridX();
	size_t destroyedY = alien->GetIndexInGridY();

	--aliensCount;
	aliensGrid[destroyedY][destroyedX] = nullptr;

	if (frontLine[destroyedX] == alien)
	{
		for (int y = destroyedY - 1; y >= 0; --y)
		{
			if (aliensGrid[y][destroyedX] != nullptr)
			{
				frontLine[destroyedX] = aliensGrid[y][destroyedX];
				return;
			}
		}
	}
	
	//all column eliminated
	frontLine[destroyedX] = nullptr;
}

size_t AliensController::GetFrontlineMinY()
{
	size_t min = SIZE_MAX;
	for (Alien* alien : frontLine)
		if (alien != nullptr && alien->GetPosY() < min)
			min = alien->GetPosY();

	return min;
}