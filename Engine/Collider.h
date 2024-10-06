#pragma once
#include "GameObject.h"
#include <unordered_set>
#include <array>

template<typename T> using uset = std::unordered_set<T>;

class Collider : public GameObject
{
friend class Simulation;

//---------------------------------------------------------- Fields

protected:
	std::array<uset<Collider*>,4> collisions;

//---------------------------------------------------------- Methods
public:
	using GameObject::GameObject;

protected:
	
	virtual void OnCollisionEnter(Collider* other, Direction collisionDir){}
	virtual void OnCollisionExit(Direction endingCollisionDir){}
	
private:
	void CALLED_BY_SIM_NotifyCollisionEnter(uset<Collider*>collidingObjects, Direction collisionDir);
	void CALLED_BY_SIM_NotifyCollisionEnter(Collider* collidingObject, Direction collisionDir);
	void CALLED_BY_SIM_UpdateEndedCollisions(const std::array<uset<Collider*>, 4>& newCollisions);
};