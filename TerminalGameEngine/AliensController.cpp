#pragma once
#include "AliensController.h"
#include "Alien.h"
#include <cassert>

AliensController::AliensController(int aliensCountX, int aliensCountY)
{
	aliensCount = aliensCountX * aliensCountY;

	aliens.resize(aliensCountY);
	for (int y = 0; y < aliensCountY; ++y)
		aliens[y].resize(aliensCountX);
}

void AliensController::Update()
{
	/*for (int y = 0; y < GetAliensGridHeight(); ++y)
	{
		for (int x = 0; x < GetAliensGridWidth(); ++x)
		{
			Alien* alien = aliens[y][x];
			if (alien != nullptr)
				alien->TryMove(aliensMoveDirectionX, GetCurrentSpeedX());
		}
	}*/
}

void AliensController::RegisterAlien(Alien* alien, int xPos, int yPos)
{
	assert(alien != nullptr);
	assert(yPos < GetAliensGridHeight());
	assert(xPos < GetAliensGridWidth());

	aliens[yPos][xPos] = alien;
	
	if (xPos == 0 && yPos == 0)
		aliensPosX = alien->GetPosX();
}