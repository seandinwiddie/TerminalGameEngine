#pragma once
#include "Alien.h"

class AlienLowScore : public Alien
{
private:
	static const Model MODEL;
//------------------------------------------------------ Methods
public:
	AlienLowScore(int xPos, int yPos) : Alien(xPos, yPos){}
	virtual size_t GetScore() const { return 10; }

protected:
	virtual void InitModel() { SetModel(MODEL); }
};



const Model AlienLowScore::MODEL =
{
	{'a', 'a', 'a', 'a'},
	{'a', 'a', 'a', 'a'}
};