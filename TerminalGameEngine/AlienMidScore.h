#pragma once
#include "Alien.h"

class AlienMidScore : public Alien
{
private:
	static const Model MODEL_1;
	static const Model MODEL_2;
	//------------------------------------------------------ Methods
public:
	AlienMidScore(int xPos, int yPos) : Alien(xPos, yPos) {}
	virtual size_t GetScore() const { return 20; }
	virtual int GetColor() const override { return Terminal::CYAN; }

protected:
	virtual void InitModel() { SetModel(MODEL_1); }
	virtual void StepAnimation() { SetModel(showFirstAnimFrame ? MODEL_1 : MODEL_2); }
};

const Model AlienMidScore::MODEL_1 =
{
	{'^', '/', '\\', '^'},
	{'d', 'O', 'O', 'b'}
};

const Model AlienMidScore::MODEL_2 =
{
	{'~', '|', '|', '~'},
	{'d', 'O', 'O', 'b'}
	
};