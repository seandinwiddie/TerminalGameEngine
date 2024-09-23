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
	//check this is ok
	std::vector<std::vector<char>> model = { {} };

protected:
	bool canMove = true;
	

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
	std::vector<std::vector<char>> CreteModelUsingChar(char c, uint sizeX, uint sizeY) const;
	virtual void Update();
	void SetModel(const std::vector<std::vector<char>>& newModel);

private:
	void ResetPartialMovement() { xPosContinuous = xPos; yPosContinuous = yPos; }
};