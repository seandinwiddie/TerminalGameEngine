#pragma once
#include "ISimulationEntity.h"
#include "GridDirection.h"
#include "AliensFrontline.h"
#include "Event.h"
#include <vector>

template <typename T> using vector = std::vector<T>;
using namespace GridDirection;

class Alien;
class SpaceInvadersLevel;
class GameObject;

class AliensController : public ISimulationEntity
{
//------------------------------------------------------------------- Aliens Settings
	const double HARDEST_WAVE = 5;
//movement
	double const BASE_MOVE_SPEED = 1;
	const double ALL_ALIENS_ELIMINATED_MOVE_SPEED_INCREASE = 0;
	const double HARDEST_WAVE_MOVE_SPEED_INCREASE = 0;

//shooting
	const double BASE_SHOTS_DELAY = 1.5;
	const double ALL_ALIENS_ELIMINATED_SHOTS_DELAY_REDUCTION = 0.7;
	const double HARDEST_WAVE_SHOTS_DELAY_REDUCTION = 0.7;
	const int SHOTS_RANDOMNESS = 0.5;

//------------------------------------------------------------------- Fields
public:
	Event<> OnWaveCompleted;

private:
	// references
	SpaceInvadersLevel* level;
	vector<vector<Alien*>> aliensGrid;
	AliensFrontline frontLine;
	
	// state
	size_t aliensCount;
	size_t aliensPosX;
	Direction xMoveDirection = Direction::right;
	bool isTimeToMoveAliensDown = false;

	double lastShotTime = -1;
	double shotDelay = 0;
//------------------------------------------------------------------- Methods
public:
	AliensController(SpaceInvadersLevel* level) : level(level) { }
;	void Reset(int aliensCountX, int aliensCountY);
	void Update() override;
	void RegisterAlien(Alien* alien, int xPos, int yPos);

private:
	double GetSpeedX()const;

	double GetNextShotDelay()const;
	double GetWaveMultiplier()const;
	double GetEliminatedAliensMultiplier()const;

	size_t GetAliensGridHeight() const { return aliensGrid.size(); }
	size_t GetAliensGridWidth() const { return GetAliensGridHeight() == 0 ? 0 : aliensGrid[0].size(); }
	size_t GetStartingAliensCount() const { return GetAliensGridWidth() * GetAliensGridHeight(); }
	size_t GetDestroyedAliensCount() const { return GetStartingAliensCount() - aliensCount; }

	void OnAlienMovedCallback(GameObject* alien, Direction moveDirection);
	void OnAlienDestroyedCallback(GameObject* alienObj);
	void OnAliensReachMargin();
	void MoveAliens(Direction dir, double speed);
	void HandleShooting();
	void HandleMovement();
};