#pragma once
#include "AliensController.h"
#include "Alien.h"
#include "Level.h"
#include <cassert>

AliensController::AliensController(Level* level, int aliensCountX, int aliensCountY) : level(level)
{
	aliensCount = aliensCountX * aliensCountY;

	aliens.resize(aliensCountY);
	for (int y = 0; y < aliensCountY; ++y)
		aliens[y].resize(aliensCountX);

}

void AliensController::Update()
{
	MoveAliens(xMoveDirection, GetMovementSpeedX());
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
		[this](int xIndex, int yIndex) { aliens[yIndex][xIndex] = nullptr; }
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
	MoveAliens(Direction::down, 9999);
}