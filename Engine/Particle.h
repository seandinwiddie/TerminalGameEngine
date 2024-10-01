#pragma once
#include "ISimulationEntity.h"
#include "GridDirection.h"
#include "GameObject.h"
#include <vector>
#include <optional>

template<typename T> using vector = std::vector<T>;
using Direction = GridDirection::Direction;

class Particle : public GameObject
{
private:
	vector<Direction> moveDirections;
	vector<double> moveSpeeds;
	char modelChar;
	size_t remainingMovementsBeforeDestruction;
	int color;
	Model model;
	
public:
	Particle
	(
		int xPos, 
		int yPos, 
		char modelChar,
		int color, 
		double moveSpeed,
		size_t movementLifeTime,
		std::optional<Direction> mainDirection
	);

	virtual bool CanExitScreenSpace() const override { return true; }
	virtual double GetGravityScale() const override { return 0; }
	virtual int GetColor() const { return color; }

protected:
	virtual void InitModel();
	virtual void Update();
	
private:
	void OnMoveCallback();
};