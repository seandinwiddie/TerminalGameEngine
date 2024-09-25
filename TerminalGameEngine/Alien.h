#pragma once
#include "GameObject.h"
#include "TimeHelper.h"

class Alien : public GameObject
{

protected:
	bool showFirstAnimFrame;
//------------------------------------------------------ Methods
public:
	Alien(int xPos, int yPos) : GameObject(xPos, yPos) { }

	virtual bool CanExitScreenSpace() const override { return false; }
	virtual double GetGravityScale() const override { return 0; }
	virtual size_t GetScore() const = 0;

	virtual void Update()
	{
		bool showFirstAnimFrameNew = TimeHelper::Instance().IsTimeForFirstOfTwoModels(1);
		if (showFirstAnimFrame != showFirstAnimFrameNew)
		{
			StepAnimation();
			showFirstAnimFrame = showFirstAnimFrameNew;
		}
	}

	virtual void StepAnimation() = 0;
};