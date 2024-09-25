#pragma once
#include "Alien.h"
#include "TimeHelper.h"	

class AlienLowScore : public Alien
{
private:
	static const Model MODEL_1;
	static const Model MODEL_2;
//------------------------------------------------------ Methods
public:
	AlienLowScore(int xPos, int yPos) : Alien(xPos, yPos){}
	virtual size_t GetScore() const { return 10; }

protected:
	virtual void InitModel() { SetModel(MODEL_1); }

	virtual void Update()
	{
		Alien::Update();
		SetModel(TimeHelper::Instance().IsTimeForFirstOfTwoModels(0.8) ? MODEL_1 : MODEL_2);
	}
};

const Model AlienLowScore::MODEL_1 =
{
	{'/', '"', '"', '\\'},
	{'{', '@', '@', '}'}
};

const Model AlienLowScore::MODEL_2 =
{
	{' ', '\\', '/', ' '},
	{'{', '@', '@', '}'}
};