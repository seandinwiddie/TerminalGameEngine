#pragma once
#include "Enemy.h"
#include "Terminal.h"
#include "GridDirection.h"

#include <vector>

using Direction = GridDirection::Direction;

class Ufo : public Enemy
{
//------------------------------------------------------ Fields
private:
	static const Model MODEL_1;
	static const vector<size_t> POSSIBLE_SCORES;
	static const size_t MOVE_SPEED = 8;

	Direction moveDirection;
//------------------------------------------------------ Methods
public:
	Ufo(int xPos, int yPos, Direction moveDirection) : Enemy(xPos, yPos), moveDirection(moveDirection) {};

	virtual bool CanExitScreenSpace() const override { return true; }
	virtual int GetColor() const override { return Terminal::RED; }
	virtual void InitModel() { SetModel(MODEL_1); }
	virtual size_t GetScore() const;
	virtual void Update() override;
};