#pragma once
#include "Config.h"
#include "AliensController.h"
#include "Alien.h"
#include "Level.h"
#include "TimeHelper.h"
#include "SpaceInvadersLevel.h"
#include "DebugManager.h"
#include "RandomUtils.h"
#include "GameObject.h"
#include <cassert>

namespace SpaceInvaders
{
	using string = std::string;
	using Collider = Engine::Collider;

	double AliensController::GetSpeedX() const
	{
		return BASE_MOVE_SPEED +
			GetEliminatedAliensMultiplier() * ALL_ALIENS_ELIMINATED_MOVE_SPEED_INCREMENT +
			GetWaveMultiplier() * WAVE_NUMBER_SPEED_INCREASE_FACTOR;
	}

	double AliensController::GetNextShotDelay()const
	{
		double delay = BASE_SHOOT_DELAY -
			GetEliminatedAliensMultiplier() * ALL_ALIENS_ELIMINATED_SHOOT_DELAY_REDUCTION -
			GetWaveMultiplier() * WAVE_NUMBER_SHOT_DELAY_REDUCTION_FACTOR +
			RandomUtils::GetRandomDouble(-SHOTS_RANDOMNESS / 2, SHOTS_RANDOMNESS / 2);

		return delay > MIN_SHOW_DELAY ? delay : MIN_SHOW_DELAY;
	}

	double AliensController::GetEliminatedAliensMultiplier()const
	{
		return static_cast<double>(GetDestroyedAliensCount()) / (GetStartingAliensCount() - 1);
	}

	double AliensController::GetWaveMultiplier()const
	{
		return static_cast<double>((level->GetWaveNumber() - 1));
	}

	void AliensController::Reset(int aliensCountX, int aliensCountY)
	{
		aliensCount = aliensCountX * aliensCountY;
		aliensGrid.Resize(aliensCountX, aliensCountY);
		frontLine.Init(aliensCountX);
	}

	void AliensController::Update()
	{
#if DEBUG_MODE
		string totBoost = "tot boost: " + std::to_string(GetSpeedX());
		string eliminationsBoost = " elim. multiplier:" + std::to_string(GetEliminatedAliensMultiplier());
		string waveBoost = " wave multiplier:" + std::to_string(GetWaveMultiplier());
		string debugStr = totBoost + " | " + eliminationsBoost + " | " + waveBoost;
		Engine::DebugManager::Instance().PrintGenericLog(debugStr, 0);
#endif

		HandleMovement();
		HandleShooting();
	}

	void AliensController::RegisterAlien(shared_ptr<Alien> alien, int xPos, int yPos)
	{
		assert(alien != nullptr);
		assert(yPos < GetAliensGridHeight());
		assert(xPos < GetAliensGridWidth());

		aliensGrid.Get(xPos, yPos) = alien;

		if (yPos == GetAliensGridHeight() - 1)
			frontLine.Set(xPos, alien);

		alien->OnMove.Subscribe
		(
			[this](shared_ptr<GameObject> alien, Direction dir) { OnAlienMovedCallback(alien, dir); }
		);

		alien->OnDestroyEvent.Subscribe
		(
			[this](shared_ptr<Collider> alienObj) { OnAlienDestroyedCallback(alienObj); }
		);
	}

	void AliensController::OnAlienMovedCallback(shared_ptr<GameObject> alien, Direction moveDirection)
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
			{
				shared_ptr<Alien> alien = aliensGrid.Get(x, y).lock();
				if (alien)
					alien->TryMove(dir, speed);
			}
				
	}

	void AliensController::OnAliensReachMargin()
	{
		xMoveDirection = DirectionUtils::GetInverseDirection(xMoveDirection);
		isTimeToMoveAliensDown = true;
	}

	static int calledTimes = 0;

	void AliensController::OnAlienDestroyedCallback(shared_ptr<GameObject> alienObj)
	{
		shared_ptr<Alien> alien = std::dynamic_pointer_cast<Alien>(alienObj);
		aliensGrid.Get(alien->GetIndexInGridX(), alien->GetIndexInGridY()).reset();
		frontLine.ReplaceDestroyedElement(alien, aliensGrid);

		--aliensCount;
		if (aliensCount == 0)
			OnWaveCompleted.Notify();
	}

	void AliensController::HandleShooting()
	{
		if (Engine::TimeHelper::Instance().GetTime() - lastShotTime > shotDelay)
		{
			shared_ptr<Alien> frontLineAlien = frontLine.GetRandom();
			if (frontLineAlien == nullptr)
				return;
			frontLineAlien->Shot();
			lastShotTime = Engine::TimeHelper::Instance().GetTime();
			shotDelay = GetNextShotDelay();
		}
	}

	void AliensController::HandleMovement()
	{
		if (isTimeToMoveAliensDown)
		{
			if (frontLine.GetMinY() - 1 <= level->GAME_OVER_Y)
				OnGroundTouched.Notify();

			MoveAliens(Direction::down, 9999);
			isTimeToMoveAliensDown = false;
		}
		else
			MoveAliens(xMoveDirection, GetSpeedX());
	}
}