#pragma once

#include "Config.h"
#include "GridDirection.h"
#include "ISimulationUpdatingEntity.h"
#include "Terminal.h"

#include <windows.h>
#include <vector>

using namespace GridDirection;

class GameObject : public ISimulationUpdatingEntity
{
//---------------------------------------------------------- Fields
public:
	friend class Simulation;
private:
	//must be modified only by simulation
	int xPos;
	int yPos;

	float xPosContinuous;
	float yPosContinuous;

	bool mustBeReprinted = true;
	std::vector<std::vector<char>> model = { {} };

protected:
	bool canMove = true;
	std::vector<bool> collidingDirections = { false,false,false,false };
	

//---------------------------------------------------------- Methods
public:
	GameObject(int xPos, int yPos);

	int GetPosX() const { return xPos; }
	int GetPosY() const { return yPos; }

	int GetMaxPosX() const { return xPos + GetModelWidth() - 1; }
	int GetMaxPosY() const { return yPos + GetModelHeight() - 1; }

	uint GetModelWidth() const;
	uint GetModelHeight() const { return model.size(); }
	const std::vector<std::vector<char>>& GetModel() const { return model; }

	virtual int GetColor() const { return Terminal::WHITE; }
	virtual bool CanExitScreenSpace() const = 0;
	virtual float GetGravityScale() const = 0;

protected:
	virtual void Move(Direction direction, float moveSpeed);
	virtual void Update();
	virtual void OnCollisionEnter(GameObject* other, Direction collisionDirection) = 0;
	virtual void OnCollisionExit(Direction collisionDirection) = 0;

	std::vector<std::vector<char>> CreteModelUsingChar(char c, uint sizeX, uint sizeY) const;
	void SetModel(const std::vector<std::vector<char>>& newModel);

private:
	void ResetPartialMovement() { xPosContinuous = xPos; yPosContinuous = yPos; }

	void CALLED_BY_SIM_NotifyCollision(GameObject* other, Direction collisionDirection);
	void CALLED_BY_SIM_UpdateCollidingDirecitons(const std::vector<bool>& newCollidingDirections);
};