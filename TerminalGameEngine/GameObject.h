#pragma once
#include "Config.h"
#include "GridDirection.h"
#include "ISimulationUpdatingEntity.h"
#include "Terminal.h"

#include <Windows.h>
#include <vector>
#include <unordered_set>

using namespace GridDirection;
using Model = std::vector<std::vector<char>>;
template<typename T> using uset = std::unordered_set<T>;
template<typename T> using vector = std::vector<T>;

class GameObject : public ISimulationUpdatingEntity
{
friend class Simulation;

//---------------------------------------------------------- Fields
private:
	int xPos;
	int yPos;

	double xPosContinuous;
	double yPosContinuous;

	bool mustBeReprinted = true;
	const Model* model = nullptr;

protected:
	bool canMove = true;
	vector<uset<GameObject*>> collisions;

//---------------------------------------------------------- Methods
public:
	virtual int GetColor() const { return Terminal::WHITE; }
	virtual bool CanExitScreenSpace() const = 0;
	virtual double GetGravityScale() const = 0;

	void Init() { InitModel(); }
	GameObject(int xPos, int yPos);
	int GetPosX() const { return xPos; }
	int GetPosY() const { return yPos; }
	int GetMaxPosX()const { return xPos + static_cast<int>(GetModelWidth()) - 1; }
	int GetMaxPosY()const { return yPos + static_cast<int>(GetModelHeight()) - 1; }
	size_t GetModelWidth()const;
	size_t GetModelHeight()const { return GetModel().size(); }
	const Model& GetModel()const { return *model; }

protected:
	virtual void Move(Direction direction, double moveSpeed);
	virtual void Update();
	virtual void OnCollisionEnter(GameObject* other, Direction collisionDir) = 0;
	virtual void OnCollisionExit(Direction endingCollisionDir) = 0;
	virtual void InitModel() = 0;

	Model CreteModelUsingChar(char modelChar, size_t sizeX, size_t sizeY) const;
	void SetModel(const Model& newModel);

private:
	void ResetPartialMovement() { xPosContinuous = xPos; yPosContinuous = yPos; }
	void ApplyGravity();

	void CALLED_BY_SIM_Move(Direction direction);
	void CALLED_BY_SIM_NotifyCollisionEnter(uset<GameObject*>collidingObjects, Direction collisionDir);
	void CALLED_BY_SIM_NotifyCollisionEnter(GameObject* collidingObject, Direction collisionDir);
	void CALLED_BY_SIM_UpdateEndedCollisions(const vector<uset<GameObject*>>& collisions);
};