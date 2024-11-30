#include "Collider.h"
#include "TimeHelper.h"
#include "Simulation.h"

namespace Engine
{
	void Collider::CALLED_BY_SIM_NotifyCollisionEnter(uset<shared_ptr<Collider>>collidingObjects, Direction collisionDir)
	{
		auto& directionCollisions = collisions[collisionDir];
		for (auto obj : collidingObjects)
		{
			if (directionCollisions.find(obj) == directionCollisions.end())
			{
				directionCollisions.insert(obj);
				OnCollisionEnter(obj, collisionDir);
			}
		}
	}

	void Collider::CALLED_BY_SIM_NotifyCollisionEnter(shared_ptr<Collider> collidingObject, Direction collisionDir)
	{
		CALLED_BY_SIM_NotifyCollisionEnter(uset<shared_ptr<Collider>>{collidingObject}, collisionDir);
	}

	void Collider::CALLED_BY_SIM_UpdateEndedCollisions(const std::array<uset<shared_ptr<Collider>>, 4>& newCollisions)
	{
		for (int i = 0; i < newCollisions.size(); ++i)
		{
			uset<shared_ptr<Collider>>& directionCollisions = collisions[i];
			const uset<shared_ptr<Collider>>& directionNewCollisions = newCollisions[i];

			list<shared_ptr<Collider>> toRemove;

			//update collision direction
			for (shared_ptr<Collider> collider : directionCollisions)
				if (directionNewCollisions.find(collider) == directionNewCollisions.end())
					toRemove.push_back(collider);

			for (shared_ptr<Collider> toRemoveObj : toRemove)
				directionCollisions.erase(toRemoveObj);

			//call on collision exit
			if (toRemove.size() > 0)
				OnCollisionExit(static_cast<Direction>(i));
		}
	}
}