#pragma once

#include "GameObject.h"

class CollidingObject : public GameObject
{
	friend class Simulation;

//---------------------------------------------------------- Fields
protected:
	std::vector<bool> collidingDirections = {false,false,false,false};

//---------------------------------------------------------- Methods
public:
	CollidingObject(int xPos, int yPos) : GameObject(xPos, yPos) {};

private:
	//called by simulation
	void NotifyCollision(CollidingObject* other, Direction collisionDirection);
	//called by simulation
	void UpdateCollidingDirecitons(const std::vector<bool>& newCollidingDirections);

protected:
	virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) = 0;
	virtual void OnCollisionExit(Direction collisionDirection) = 0;
};