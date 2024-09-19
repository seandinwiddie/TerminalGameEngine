#include "MovingStraightObject.h"

MovingStraightObject::MovingStraightObject(int xPos, int yPos, Direction moveDir, float moveSpeed)
:CollidingObject(xPos, yPos), moveDirection(moveDir), moveSpeed(moveSpeed)
{
	canMove = true;
}

void MovingStraightObject::Update()
{
	CollidingObject::Update();

	if (canMove)
		MoveContinuous(moveDirection, moveSpeed);
}