#pragma once
#include "Level.h"

class ScoreLevel : public Level
{
protected:
    virtual void ShowGameOverScreen(int score, int bestScore) = 0;
	virtual void OnPostGameOverDelayEnded() override;
};