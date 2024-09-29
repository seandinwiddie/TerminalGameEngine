#pragma once
#include "Alien.h"

class AlienMidScore : public Alien
{
private:
	static const Model MODEL_1;
	static const Model MODEL_2;
	//------------------------------------------------------ Methods
public:
	using Alien::Alien;

	virtual size_t GetScore() const { return 20; }
	virtual int GetColor() const override { return Terminal::CYAN; }

protected:
	virtual void InitModel() { SetModel(MODEL_1); }
	virtual void StepAnimation() { SetModel(isFirsAnimationFrameTime ? MODEL_1 : MODEL_2); }
};

const Model AlienMidScore::MODEL_1 =
{
	{ '(', 'o', 'O', ')' },
	{ 'V', '~', '~', 'v' }
};

const Model AlienMidScore::MODEL_2 =
{
	{ '(', 'O', 'o', ')' },
	{ 'v', '~', '~', 'V' }
};