#pragma once

#include "Config.h"
#include "GridDirection.h"
#include "ISimulationObject.h"
#include <vector>

using namespace GridDirection;

class TransformObject : public SimulationObject
{
//---------------------------------------------------------- Fields
public:
	friend class Simulation;

private:
	int xPos;
	int yPos;
	float xPosContinuous;
	float yPosContinuous;

protected:
	bool canMove = true;
	float lastTimeMovedInGrid = 0;
	std::vector<std::vector<char>> model = { {} };

//---------------------------------------------------------- Methods
public:
	TransformObject(int xPos, int yPos);

	int GetPosX() const { return xPos; }
	int GetPosY() const { return yPos; }

	int GetMaxPosX() const { return xPos + GetModelWidth() - 1; }
	int GetMaxPosY() const { return yPos + GetModelHeight() - 1; }

	int GetScreenPosX(int padding) const { return xPos - padding; }
	int GetScreenPosY(int padding) const { return yPos - padding; }

	uint GetModelWidth() const;
	uint GetModelHeight() const { return model.size(); }
	const std::vector<std::vector<char>>& GetModel() const { return model; }

	virtual bool CanExitScreenSpace() const = 0;
	virtual float GetGravityScale() const = 0;

protected:
	virtual void Move(Direction direction, float moveSpeed);
	std::vector<std::vector<char>> CreteModelUsingChar(char c, uint sizeX, uint sizeY) const;
	virtual void Update();

private:
	void ResetPartialMovement() { xPosContinuous = xPos; yPosContinuous = yPos; }
};