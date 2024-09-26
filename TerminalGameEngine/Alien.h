#pragma once
#include "GameObject.h"

class Alien : public GameObject
{
protected:
	bool showFirstAnimFrame;
//------------------------------------------------------ Methods
public:
	Alien(int xPos, int yPos) : GameObject(xPos, yPos) { }

public:
	virtual bool CanExitScreenSpace() const override { return false; }
	virtual size_t GetScore() const = 0;

protected:
	virtual double GetGravityScale() const override { return 0; }
	virtual void CALLED_BY_SIM_OnDestroy() override;

	virtual void Update();

	virtual void StepAnimation() = 0;
};