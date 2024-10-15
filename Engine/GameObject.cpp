#include "GameObject.h"
#include "TimeHelper.h"
#include "Simulation.h"

namespace Engine
{
	GameObject::GameObject(int xPos, int yPos) :
		xPos(xPos),
		yPos(yPos),
		xPosContinuous(xPos),
		yPosContinuous(yPos)
	{
		ResetPartialMovement();
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
			TryMove(Direction::down, gravityScale);
		else
			TryMove(Direction::up, gravityScale);
	}

	void GameObject::TryMove(Direction direction, double moveSpeed)
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
		result.Resize(sizeX, sizeY);

		for (auto& elem : result)
			elem = modelChar;

		return result;
	}

	void GameObject::SetModel(const Model& newModel)
	{
		if (model == &newModel)
			return;

		model = &newModel;
		Simulation::Instance().MarkAreaToReprint(this);
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
		OnMove.Notify(this, direction);
	}

	//todo pass comparison lambda instead of using 2 functions
	void GameObject::InsertInListHighSortingLayerFirst(GameObject* obj, std::list<GameObject*>& list)
	{
		auto it = list.begin();
		for (; it != list.end(); ++it)
			if (obj->GetSortingLayer() >= (*it)->GetSortingLayer())
				break;
		list.insert(it, obj);
	}

	void GameObject::InsertInListLowSortingLayerFirst(GameObject* obj, std::list<GameObject*>& list)
	{
		auto it = list.begin();
		for (; it != list.end(); ++it)
			if (obj->GetSortingLayer() <= (*it)->GetSortingLayer())
				break;
		list.insert(it, obj);
	}
}