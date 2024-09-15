#pragma once

#include "TransformObject.h"

class CollidingObject : public TransformObject
{
	friend class Simulation;

//---------------------------------------------------------- Fields
protected:
	std::vector<bool> collidingDirections = { false,false,false,false };

//---------------------------------------------------------- Methods
public:
	CollidingObject(const int xPos, const int yPos) : TransformObject(xPos, yPos) {};

private:
	//called by simulation
	void NotifyCollision(CollidingObject* other, const Direction collisionDirection);
	//called by simulation
	void UpdateCollidingDirecitons(const std::vector<bool>& newCollidingDirections);

protected:
	virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) = 0;
	virtual void OnCollisionExit(Direction collisionDirection) = 0;
};