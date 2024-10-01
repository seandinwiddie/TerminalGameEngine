#pragma once
#include "KinematicObject.h"
#include <unordered_set>

template<typename T> using uset = std::unordered_set<T>;

class GameObject : public KinematicObject
{
friend class Simulation;

//---------------------------------------------------------- Fields

protected:
	vector<uset<GameObject*>> collisions;

private:
	int xPos;
	int yPos;

	double xPosContinuous;
	double yPosContinuous;

	bool mustBeReprinted = true;
	const Model* model = nullptr;

//---------------------------------------------------------- Methods
public:
	GameObject(int xPos, int yPos):KinematicObject(xPos, yPos){ collisions.resize(4); }

protected:
	
	virtual void OnCollisionEnter(GameObject* other, Direction collisionDir){}
	virtual void OnCollisionExit(Direction endingCollisionDir){}
	
private:
	void CALLED_BY_SIM_NotifyCollisionEnter(uset<GameObject*>collidingObjects, Direction collisionDir);
	void CALLED_BY_SIM_NotifyCollisionEnter(GameObject* collidingObject, Direction collisionDir);
	void CALLED_BY_SIM_UpdateEndedCollisions(const vector<uset<GameObject*>>& collisions);
};