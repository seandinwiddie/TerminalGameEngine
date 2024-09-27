#pragma once
#include "AliensController.h"
#include "Alien.h"
#include "Level.h"
#include "TimeHelper.h"
#include "SpaceInvadersLevel.h"
#include "DebugManager.h"
#include <cassert>

double AliensController::GetSpeedX() const
{
	auto t1 = GetEliminatedAliensSpeedBoost();
	auto t = GetWaveSpeedBoost();
	
	return BASE_MOVE_SPEED + GetEliminatedAliensSpeedBoost() + GetWaveSpeedBoost();
}

double AliensController::GetEliminatedAliensSpeedBoost()const
{
	auto t1 = GetDestroyedAliensCount();
	auto t = GetStartingAliensCount();
	auto t3 = aliensCount;

	return static_cast<double>(GetDestroyedAliensCount()) / GetStartingAliensCount() * ALL_ALIENS_ELIMINATED_SPEED_INCREASE;
}

double AliensController::GetWaveSpeedBoost()const
{
	auto t1 = level->GetWaveNumber() / MAX_SPEED_WAVE * HARDEST_WAVE_SPEED_INCREASE;

	return level->GetWaveNumber() / MAX_SPEED_WAVE * HARDEST_WAVE_SPEED_INCREASE;
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
	double delayReduction1 = GetEliminatedAliensSpeedBoost();
	double delayReduction2 = GetWaveSpeedBoost();
	string debugStr = std::to_string(GetSpeedX()) + " - " + std::to_string(delayReduction1) + " - " + std::to_string(delayReduction2);
	DebugManager::Instance().PrintGenericLog(debugStr);

	if (isTimeToMoveAliensDown)
	{
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