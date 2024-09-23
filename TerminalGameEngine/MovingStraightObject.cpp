#include "MovingStraightObject.h"

MovingStraightObject::MovingStraightObject(int xPos, int yPos, Direction moveDir, float moveSpeed)
:GameObject(xPos, yPos), moveDirection(moveDir), moveSpeed(moveSpeed)
{
	canMove = true;
}

void MovingStraightObject::Update()
{
	GameObject::Update();

	if (canMove)
		Move(moveDirection, moveSpeed);
}