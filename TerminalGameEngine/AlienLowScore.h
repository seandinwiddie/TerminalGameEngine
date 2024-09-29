#pragma once
#include "Alien.h"

class AlienLowScore : public Alien
{
private:
	static const Model MODEL_1;
	static const Model MODEL_2;
//------------------------------------------------------ Methods
public:
	using Alien::Alien;

	virtual size_t GetScore() const { return 10; }
	virtual int GetColor() const override { return Terminal::YELLOW_DARK; }

protected:
	virtual void InitModel() { SetModel(MODEL_1); }
	virtual void StepAnimation() { SetModel(isFirsAnimationFrameTime ? MODEL_1 : MODEL_2); }
};

const Model AlienLowScore::MODEL_1 =
{
	{ '[', ':', ':', ']' },
	{ '/', '"', '"', '\\'}

};

const Model AlienLowScore::MODEL_2 =
{
	{  '[', '.', '.', ']' },
	{ '\\', '"', '"', '/' }
};