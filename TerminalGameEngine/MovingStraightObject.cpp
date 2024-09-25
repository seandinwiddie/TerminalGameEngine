#include "MovingStraightObject.h"

MovingStraightObject::MovingStraightObject(int xPos, int yPos, Direction moveDir, double moveSpeed)
:GameObject(xPos, yPos), moveDirection(moveDir), moveSpeed(moveSpeed){ }

void MovingStraightObject::Update()
{
	GameObject::Update();

	if (canMove)
		TryMove(moveDirection, moveSpeed);
}