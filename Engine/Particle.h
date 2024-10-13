#pragma once
#include "ISimulationEntity.h"
#include "GridDirection.h"
#include "GameObject.h"
#include <array>
#include <optional>

using Direction = GridDirection::Direction;
template<typename T, std::size_t N> using array = std::array<T, N>;

class Particle : public GameObject
{
private:
	array<Direction,2> moveDirections;
	array<double,2> moveSpeeds;

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