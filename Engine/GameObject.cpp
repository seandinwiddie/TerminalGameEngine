#include "GameObject.h"
#include "TimeHelper.h"
#include "Simulation.h"

void GameObject::CALLED_BY_SIM_NotifyCollisionEnter(uset<GameObject*>collidingObjects, Direction collisionDir)
{
	uset<GameObject*>& directionCollisions = collisions[collisionDir];
	for (GameObject* obj : collidingObjects)
	{
		if (directionCollisions.find(obj) == directionCollisions.end())
		{
			directionCollisions.insert(obj);
			OnCollisionEnter(obj, collisionDir);
		}
	}
}

void GameObject::CALLED_BY_SIM_NotifyCollisionEnter(GameObject* collidingObject, Direction collisionDir)
{
	CALLED_BY_SIM_NotifyCollisionEnter(uset<GameObject*>{collidingObject}, collisionDir);
}

void GameObject::CALLED_BY_SIM_UpdateEndedCollisions(const vector<uset<GameObject*>>& newCollisions)
{
	assert(newCollisions.size() == 4);

	for (int i = 0; i < newCollisions.size(); ++i)
	{
		uset<GameObject*>& directionCollisions = collisions[i];
		const uset<GameObject*>& directionNewCollisions = newCollisions[i];

		list<GameObject*> toRemove;

		//update collision direction
		for(GameObject* collider : directionCollisions)
			if (directionNewCollisions.find(collider) == directionNewCollisions.end())
				toRemove.push_back(collider);

		for (GameObject* toRemoveObj : toRemove)
			directionCollisions.erase(toRemoveObj);

		//call on collision exit
		if(toRemove.size() > 0)
			OnCollisionExit(static_cast<Direction>(i));
	}
}

