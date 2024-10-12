#include "Collider.h"
#include "TimeHelper.h"
#include "Simulation.h"

void Collider::CALLED_BY_SIM_NotifyCollisionEnter(uset<Collider*>collidingObjects, Direction collisionDir)
{
	uset<Collider*>& directionCollisions = collisions[collisionDir];
	for (Collider* obj : collidingObjects)
	{
		if (directionCollisions.find(obj) == directionCollisions.end())
		{
			directionCollisions.insert(obj);
			OnCollisionEnter(obj, collisionDir);
		}
	}
}

void Collider::CALLED_BY_SIM_NotifyCollisionEnter(Collider* collidingObject, Direction collisionDir)
{
	CALLED_BY_SIM_NotifyCollisionEnter(uset<Collider*>{collidingObject}, collisionDir);
}

void Collider::CALLED_BY_SIM_UpdateEndedCollisions(const std::array<uset<Collider*>,4>& newCollisions)
{
	for (int i = 0; i < newCollisions.size(); ++i)
	{
		uset<Collider*>& directionCollisions = collisions[i];
		const uset<Collider*>& directionNewCollisions = newCollisions[i];

		list<Collider*> toRemove;

		//update collision direction
		for (Collider* collider : directionCollisions)
			if (directionNewCollisions.find(collider) == directionNewCollisions.end())
				toRemove.push_back(collider);

		for (Collider* toRemoveObj : toRemove)
			directionCollisions.erase(toRemoveObj);

		//call on collision exit
		if(toRemove.size() > 0)
			OnCollisionExit(static_cast<Direction>(i));
	}
}

