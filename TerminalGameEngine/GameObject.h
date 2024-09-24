#pragma once
#include "Config.h"
#include "GridDirection.h"
#include "ISimulationUpdatingEntity.h"
#include "Terminal.h"

#include <windows.h>
#include <vector>

using namespace GridDirection;
using Model = std::vector<std::vector<char>>;

class GameObject : public ISimulationUpdatingEntity
{
friend class Simulation;

//---------------------------------------------------------- Fields
private:
	//don't modify directly
	int xPos;
	int yPos;

	double xPosContinuous;
	double yPosContinuous;

	bool mustBeReprinted = true;
	const Model* model = nullptr;

protected:
	bool canMove = true;
	std::vector<bool> collidingDirections{ false, false, false, false };

//---------------------------------------------------------- Methods
public:
	virtual int GetColor() const { return Terminal::WHITE; }
	virtual bool CanExitScreenSpace() const = 0;
	virtual double GetGravityScale() const = 0;

	GameObject(int xPos, int yPos);
	int GetPosX() const { return xPos; }
	int GetPosY() const { return yPos; }
	int GetMaxPosX() const { return xPos + static_cast<int>(GetModelWidth()) - 1; }
	int GetMaxPosY() const { return yPos + static_cast<int>(GetModelHeight()) - 1; }
	size_t GetModelWidth() const;
	size_t GetModelHeight() const { return model == nullptr ? 0 : model->size(); }
	const Model& GetModel();

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

	void CALLED_BY_SIM_NotifyCollisionEnter(GameObject* other, Direction collisionDir);
	void CALLED_BY_SIM_NotifyCollisionsExit(const std::vector<bool>& newCollidingDirections);
};