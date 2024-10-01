#include "MovingStraightObject.h"

MovingStraightObject::MovingStraightObject(int xPos, int yPos, Direction moveDir, double moveSpeed)
:Collider(xPos, yPos), moveDirection(moveDir), moveSpeed(moveSpeed){ }

void MovingStraightObject::Update()
{
	Collider::Update();

	if (canMove)
		TryMove(moveDirection, moveSpeed);
}