#include "CollidingObject.h"

void CollidingObject::NotifyCollision(CollidingObject* other, Direction collisionDirection)
{
	int directionIndex = static_cast<int>(collisionDirection);
	if (collidingDirections[directionIndex] == false)
	{
		collidingDirections[directionIndex] = true;
		OnCollisionEnter(other, collisionDirection);
	}
}

void CollidingObject::UpdateCollidingDirecitons(const std::vector<bool>& newCollidingDirections)
{
	for (int i = 0; i < collidingDirections.size(); ++i)
	{
		if (collidingDirections[i] == true && newCollidingDirections[i] == false)
		{
			collidingDirections[i] = false;
			OnCollisionExit(static_cast<Direction>(i));
		}
	}
}