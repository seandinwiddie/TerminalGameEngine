#pragma once

#include "Config.h"
#include "GridDirection.h"
#include "SimulationObject.h"
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
	TransformObject(const int xPos, const int yPos);

	int GetPosX() const { return xPos; }
	int GetPosY() const { return yPos; }

	int GetMaxPosX() const { return xPos + GetModelWidth() - 1; }
	int GetMaxPosY() const { return yPos + GetModelHeight() - 1; }

	int GetScreenPosX(const int padding) { return xPos - padding; }
	int GetScreenPosY(const int padding) { return yPos - padding; }

	int GetModelWidth() const;
	int GetModelHeight() const { return model.size(); }
	const std::vector<std::vector<char>>& GetModel() const { return model; }

	virtual bool CanExitScreenSpace() const = 0;
	virtual float GetGravityScale() const = 0;

protected:
	virtual void Move(const Direction direction, const float moveSpeed);
	std::vector<std::vector<char>> CreteModelUsingChar(char c, const uint sizeX, const uint sizeY) const;
	virtual void Update();

private:
	void ResetPartialMovement() { xPosContinuous = xPos; yPosContinuous = yPos; }
};