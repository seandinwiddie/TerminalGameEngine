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
	for (int y = 0; y < GetAliensGridHeight(); ++y)
	{
		for (int x = 0; x < GetAliensGridWidth(); ++x)
		{
			Alien* alien = aliens[y][x];
			if (alien != nullptr)
				alien->TryMove(aliensMoveDirectionX, GetCurrentSpeedX());
		}
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
		[this](GameObject* alien, Direction dir) { OnAnyAlienMovedCallback(alien, dir); }
	);
}

void AliensController::OnAnyAlienMovedCallback(GameObject* alien, Direction moveDirection)
{
	if (moveDirection == aliensMoveDirectionX)
	{
		int alienXPos = alien->GetPosX();
		if (alienXPos == level->GetScreenPadding() || alienXPos == level->GetScreenMaxX() - alien->GetModelWidth())
			aliensMoveDirectionX = GetInverseDirection(aliensMoveDirectionX);
	}
}