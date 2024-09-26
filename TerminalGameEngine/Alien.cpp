#include "Alien.h"
#include "TimeHelper.h"

void Alien::Update()
{
	bool showFirstAnimFrameNew = TimeHelper::Instance().IsTimeForFirstOfTwoModels(1);
	if (showFirstAnimFrame != showFirstAnimFrameNew)
	{
		StepAnimation();
		showFirstAnimFrame = showFirstAnimFrameNew;
	}
}