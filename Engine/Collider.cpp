#include "Collider.h"
#include "TimeHelper.h"
#include "Simulation.h"

namespace Engine
{
	// todo move to utility class and make templatic
	//----------------------------------------- weak ptr list utils
	bool WeakPtrListContainsShared(const list<weak_ptr<Collider>>& list, const shared_ptr<Collider>& sharedPtr)
	{
		for (const auto& weakItem : list)
			if (auto sharedItem = weakItem.lock())
				if (sharedItem == sharedPtr)
					return true;

		return false;
	}

	void RemoveWeakPointerFromList(list<weak_ptr<Collider>>& weakList, const weak_ptr<Collider>& targetWeak)
	{
		shared_ptr<Collider> target = targetWeak.lock();
		if (target == nullptr)
			return;
		
		for (auto itWeak = weakList.begin(); itWeak != weakList.end(); ++itWeak)
		{
			if (auto it = itWeak->lock())
				if (it == target)
				{
					weakList.erase(itWeak);
					return;
				}
		}
	}
	//----------------------------------------- weak ptr list utils

	void Collider::CALLED_BY_SIM_NotifyCollisionEnter(uset<shared_ptr<Collider>>collidingObjects, Direction collisionDir)
	{
		list<weak_ptr<Collider>>& localDirectionColl = collisions[collisionDir];
		for (auto obj : collidingObjects)
		{
			if(WeakPtrListContainsShared(localDirectionColl, obj) == false)
			{
				localDirectionColl.push_back(obj);
				OnCollisionEnter(obj, collisionDir);
			}
		}
	}

	void Collider::CALLED_BY_SIM_NotifyCollisionEnter(shared_ptr<Collider> collidingObject, Direction collisionDir)
	{
		CALLED_BY_SIM_NotifyCollisionEnter(uset<shared_ptr<Collider>>{collidingObject}, collisionDir);
	}

	void Collider::CALLED_BY_SIM_UpdateEndedCollisions(const std::array<uset<shared_ptr<Collider>>,4>& newCollisions)
	{
		for (int i = 0; i < newCollisions.size(); ++i)
		{
			list<weak_ptr<Collider>>& localDirectionColl = collisions[i];
			const uset<shared_ptr<Collider>>& newDirectionColl = newCollisions[i];

			list<weak_ptr<Collider>> toRemove;

			//update collision direction
			for (weak_ptr<Collider> colliderWeak : localDirectionColl)
			{
				auto collider = colliderWeak.lock();
				if (collider == nullptr || newDirectionColl.find(collider) == newDirectionColl.end())
					toRemove.push_back(colliderWeak);
			}	

			for (auto toRemoveObj : toRemove)
				RemoveWeakPointerFromList(localDirectionColl, toRemoveObj);

			//call on collision exit
			if (toRemove.size() > 0)
				OnCollisionExit(static_cast<Direction>(i));
		}
	}
}