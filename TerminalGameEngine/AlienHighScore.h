#pragma once
#include "Alien.h"

class AlienHighScore : public Alien
{
private:
	static const Model MODEL_1;
	static const Model MODEL_2;
	//------------------------------------------------------ Methods
public:
	AlienHighScore(int xPos, int yPos) : Alien(xPos, yPos) {}
	virtual size_t GetScore() const { return 30; }
	virtual int GetColor() const override { return Terminal::MAGENTA; }

protected:
	virtual void InitModel() { SetModel(MODEL_1); }
	virtual void StepAnimation() { SetModel(showFirstAnimFrame ? MODEL_1 : MODEL_2); }
};

const Model AlienHighScore::MODEL_1 =
{
	{ '/', '\'', '\'', '\\'},
	{ '/', 'O',  'o',  '\\' }
};

const Model AlienHighScore::MODEL_2 =
{
	{ '|', '\'', '\'', '|'},
	{ '/', 'o', 'O', '\\' }
};