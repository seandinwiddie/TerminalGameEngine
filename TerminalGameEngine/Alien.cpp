#include "Alien.h"
#include "TimeHelper.h"
#include "AudioManager.h"

void Alien::Update()
{
	bool showFirstAnimFrameNew = TimeHelper::Instance().IsTimeForFirstOfTwoModels(1);
	if (showFirstAnimFrame != showFirstAnimFrameNew)
	{
		StepAnimation();
		showFirstAnimFrame = showFirstAnimFrameNew;
	}
}

void Alien::CALLED_BY_SIM_OnDestroy()
{
	AudioManager::Instance().PlayFx("SpaceInv/alienDeath2.wav");
	OnDestroy.Notify(xIndexInMatrix, yIndexInMatrix);
}