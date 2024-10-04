#pragma once
#include "Alien.h"

class AlienHighScore : public Alien
{
private:
	static const Model MODEL_1;
	static const Model MODEL_2;
	//------------------------------------------------------ Methods
public:
	using Alien::Alien;

	virtual size_t GetScore() const { return 30; }
	virtual int GetColor() const override { return Terminal::MAGENTA; }

protected:
	virtual void InitModel() 
	{
		animationModel1 = &MODEL_1;
		animationModel2 = &MODEL_2;
		SetModel(MODEL_1); 
	}
};

const Model AlienHighScore::MODEL_1 =
{
	{ '/', 'O',  'o',  '\\' },
	{ '/', '\'', '\'', '\\'}
};

const Model AlienHighScore::MODEL_2 =
{
	{ '/', 'o', 'O', '\\' },
	{ '|', '\'', '\'', '|'}
};