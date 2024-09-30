#include "Enemy.h"
#include "TimeHelper.h"

void Enemy::Update()
{
	bool showFirstAnimFrameNew = TimeHelper::Instance().IsTimeForFirstOfTwoModels(1);
	if (isFirsAnimationFrameTime != showFirstAnimFrameNew)
	{
		StepAnimation();
		isFirsAnimationFrameTime = showFirstAnimFrameNew;
	}
}