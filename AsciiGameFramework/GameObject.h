#pragma once

#include <vector>
#include "GridDirection.h"

using namespace GridDirection;

class GameObject
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
	std::vector<std::vector<unsigned char>> model = { {} };

//---------------------------------------------------------- Methods
public:
	GameObject(const int xPos, const int yPos);

	int GetPosX() const { return xPos; }
	int GetPosY() const { return yPos; }

	int GetMaxPosX() const { return xPos + GetModelWidth() - 1; }
	int GetMaxPosY() const { return yPos + GetModelHeight() - 1; }

	int GetScreenPosX(const int padding) { return xPos - padding; }
	int GetScreenPosY(const int padding) { return yPos - padding; }

	int GetModelWidth() const;
	int GetModelHeight() const { return model.size(); }
	const std::vector<std::vector<unsigned char>>& GetModel() const { return model; }

	virtual bool CanExitScreenSpace() const = 0;
	virtual float GetGravityScale() const = 0;

	
	virtual void Update();

protected:
	virtual void Move(const Direction direction, const float moveSpeed);
	std::vector<std::vector<unsigned char>> CreteModelUsingChar(unsigned char c, const unsigned int sizeX, const unsigned int sizeY) const;

private:
	void ResetPartialMovement() { xPosContinuous = xPos; yPosContinuous = yPos; }
};