#pragma once
#include "GameObject.h"

class Alien : public GameObject
{
//------------------------------------------------------ Methods
public:
	Alien(int xPos, int yPos) : GameObject(xPos, yPos) { }

	virtual bool CanExitScreenSpace() const override { return false; }
	virtual double GetGravityScale() const override { return 0; }
	virtual size_t GetScore() const = 0;
};