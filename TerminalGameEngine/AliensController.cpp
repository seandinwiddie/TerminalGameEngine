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
	return BASE_MOVE_SPEED + 
		GetEliminatedAliensMultiplier() * ALL_ALIENS_ELIMINATED_MOVE_SPEED_INCREASE +
		GetWaveMultiplier() * HARDEST_WAVE_MOVE_SPEED_INCREASE;
}

double AliensController::GetShotsDelay()const
{
	return BASE_SHOTS_DELAY - 
		GetEliminatedAliensMultiplier() * ALL_ALIENS_ELIMINATED_SHOTS_DELAY_REDUCTION - 
		GetWaveMultiplier() * HARDEST_WAVE_SHOTS_DELAY_REDUCTION;
}

double AliensController::GetEliminatedAliensMultiplier()const
{
	return static_cast<double>(GetDestroyedAliensCount()) / (GetStartingAliensCount() - 1);
}

double AliensController::GetWaveMultiplier()const
{ 
	return level->GetWaveNumber() / HARDEST_WAVE;
}

AliensController::AliensController(SpaceInvadersLevel* level, int aliensCountX, int aliensCountY) : level(level)
{
	aliensCount = aliensCountX * aliensCountY;

	aliensGrid.resize(aliensCountY);
	for (int y = 0; y < aliensCountY; ++y)
		aliensGrid[y].resize(aliensCountX);

	frontLine.Init(aliensCountX);
}

void AliensController::Update()
{
#if DEBUG_MODE
	string totBoost = "tot boost: " + std::to_string(GetSpeedX());
	string eliminationsBoost = " elim. multiplier:"+ std::to_string(GetEliminatedAliensMultiplier());
	string waveBoost = " wave multiplier:" + std::to_string(GetWaveMultiplier());
	string debugStr = totBoost + " | " + eliminationsBoost + " | " + waveBoost;
	DebugManager::Instance().PrintGenericLog(debugStr,0);

	DebugManager::Instance().PrintGenericLog(std::to_string(frontLine.GetMinY()), 1);
#endif

	if (isTimeToMoveAliensDown)
	{
		if (frontLine.GetMinY() - 1 <= GAME_OVER_Y)
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
		frontLine.Set(xPos,alien);

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
		if (
			alienXPos == level->GetScreenPadding() || 
			alienXPos == level->GetWorldSizeX() - level->GetScreenPadding() - alien->GetModelWidth()
			)
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

	--aliensCount;
	aliensGrid[alien->GetIndexInGridY()][alien->GetIndexInGridX()] = nullptr;

	frontLine.ReplaceDestroyedElement(alien, aliensGrid);
}