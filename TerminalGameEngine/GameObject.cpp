#include "GameObject.h"
#include "TimeHelper.h"
#include "Simulation.h"
#include "Bunny.h" //todo remove

GameObject::GameObject(int xPos, int yPos): 
	xPos(xPos), 
	yPos(yPos), 
	xPosContinuous(xPos), 
	yPosContinuous(yPos)
{
	collisions.resize(4); //todo move in declaration
	ResetPartialMovement();
}

size_t GameObject::GetModelWidth()const
{
	if (GetModelHeight() == 0)
		return 0;
	return GetModel()[0].size();
}

void GameObject::Update()
{
	ApplyGravity();
}

void GameObject::ApplyGravity()
{
	double gravityScale = GetGravityScale();
	if (gravityScale == 0)
		return;
	if (gravityScale > 0)
		Move(Direction::down, gravityScale);
	else
		Move(Direction::up, gravityScale);
}

void GameObject::Move(Direction direction, double moveSpeed)
{
	if (canMove == false)
		return;

	moveSpeed = abs(moveSpeed);
	double deltaTime = TimeHelper::Instance().GetDeltaTime();

	switch (direction)
	{
	case Direction::up:
		yPosContinuous += moveSpeed * deltaTime;
		break;
	case Direction::down:
		yPosContinuous -= moveSpeed * deltaTime;
		break;
	case Direction::right:
		xPosContinuous += moveSpeed * deltaTime;
		break;
	case Direction::left:
		xPosContinuous -= moveSpeed * deltaTime;
		break;
	}

	if (direction == Direction::left || direction == Direction::right)
	{
		if (round(xPosContinuous) != xPos)
			Simulation::Instance().RequestMovement(this, direction, moveSpeed);
	}
	else if (round(yPosContinuous) != yPos)
		Simulation::Instance().RequestMovement(this, direction, moveSpeed);
}

Model GameObject::CreteModelUsingChar(char modelChar, size_t sizeX, size_t sizeY) const
{
	Model result;
	result.resize(sizeY);
	for (int y = 0; y < sizeY; ++y)
	{
		for (int x = 0; x < sizeX; ++x)
		{
			result[y].resize(sizeX);
			result[y][x] = modelChar;
		}
	}
	return result;
}

void GameObject::SetModel(const Model& newModel)
{
	if (model == &newModel)
		return;

	mustBeReprinted = true;
	model = &newModel;
}

void GameObject::CALLED_BY_SIM_NotifyCollisionEnter(uset<GameObject*>collidingObjects, Direction collisionDir)
{
	Bunny* b = dynamic_cast<Bunny*>(this);
	if (collisionDir != Direction::down && b != nullptr)
		int a = 1;

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

		for(GameObject* collider : directionCollisions)
			if (directionNewCollisions.find(collider) == directionNewCollisions.end())
			{
				toRemove.push_back(collider);
				OnCollisionExit(static_cast<Direction>(i));
			}

		for (GameObject* toRemoveObj : toRemove)
			directionCollisions.erase(toRemoveObj);
	}
}

void GameObject::CALLED_BY_SIM_Move(Direction direction)
{
	switch (direction)
	{
	case Direction::up:
		++yPos;
		yPosContinuous = yPos;
		break;
	case Direction::down:
		--yPos;
		yPosContinuous = yPos;
		break;
	case Direction::right:
		++xPos;
		xPosContinuous = xPos;
		break;
	case Direction::left:
		--xPos;
		xPosContinuous = xPos;
		break;
	}
}

