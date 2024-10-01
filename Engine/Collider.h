#pragma once
#include "GameObject.h"
#include <unordered_set>

template<typename T> using uset = std::unordered_set<T>;

class Collider : public GameObject
{
friend class Simulation;

//---------------------------------------------------------- Fields

protected:
	vector<uset<Collider*>> collisions;

//---------------------------------------------------------- Methods
public:
	Collider(int xPos, int yPos):GameObject(xPos, yPos){ collisions.resize(4); }

protected:
	
	virtual void OnCollisionEnter(Collider* other, Direction collisionDir){}
	virtual void OnCollisionExit(Direction endingCollisionDir){}
	
private:
	void CALLED_BY_SIM_NotifyCollisionEnter(uset<Collider*>collidingObjects, Direction collisionDir);
	void CALLED_BY_SIM_NotifyCollisionEnter(Collider* collidingObject, Direction collisionDir);
	void CALLED_BY_SIM_UpdateEndedCollisions(const vector<uset<Collider*>>& collisions);
};