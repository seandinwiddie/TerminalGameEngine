#include "MovingStraightObject.h"

MovingStraightObject::MovingStraightObject(const int xPos, const int yPos, const Direction moveDir, const float moveSpeed) :
	CollidingObject(xPos, yPos), moveDirection(moveDir), moveSpeed(moveSpeed)
{
	canMove = true;
}

void MovingStraightObject::Update()
{
	CollidingObject::Update();

	if (canMove)
		Move(moveDirection, moveSpeed);
}