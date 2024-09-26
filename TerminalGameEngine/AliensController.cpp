#pragma once
#include "AliensController.h"
#include "Alien.h"
#include <cassert>

AliensController::AliensController(int aliensCountX, int aliensCountY) : aliensCountX(aliensCountX), aliensCountY(aliensCountY)
{
	aliensCount = aliensCountX * aliensCountY;

	aliens.resize(aliensCountY);
	for (int y = 0; y < aliensCountY; ++y)
		aliens[y].resize(aliensCountX);
}

void AliensController::Update()
{
	for (int y = 0; y < aliensCountY; ++y)
	{
		for (int x = 0; x < aliensCountX; ++x)
		{
			Alien* alien = aliens[y][x];
			if (alien != nullptr)
				alien->TryMove(currentDirection, GetCurrentSpeedX());
		}
	}
}

void AliensController::RegisterAlien(Alien* alien, int xPos, int yPos)
{
	assert(alien != nullptr);
	assert(xPos < aliensCountX);
	assert(yPos < aliensCountY);

	aliens[yPos][xPos] = alien;
}