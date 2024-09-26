#pragma once
#include "ISimulationEntity.h"
#include "GridDirection.h"
#include <vector>

template <typename T> using vector = std::vector<T>;
using namespace GridDirection;

class Alien;
class SpaceInvadersLevel;
class GameObject;

class AliensController : public ISimulationEntity
{
//------------------------------------------------------------------- Settings
	double const BEGINNING_MOVE_DELAY = 1.0;

	const double MAX_DELAY_REDUCTION_ELIMINATING_ALIENS = 1;

	const double MAX_DELAY_REDUCTION_WAVES = 0;
	const double WAVE_REACHING_MIN_DELAY = 5; //after 5th wave aliens reach max speed
//------------------------------------------------------------------- Fields
private:
	// references
	SpaceInvadersLevel* level;
	vector<vector<Alien*>> aliens;
	
	// state
	size_t aliensCount;
	size_t aliensPosX;
	Direction xMoveDirection = Direction::right;
	bool isTimeToMoveAliensDown = false;
	double lastTimeMoved = -1;

//------------------------------------------------------------------- Methods
public:
	AliensController(SpaceInvadersLevel* level, int aliensCountX, int aliensCountY);
	void Update() override;
	void RegisterAlien(Alien* alien, int xPos, int yPos);

private:
	double GetMoveDelay();
	size_t GetAliensGridHeight() { return aliens.size(); }
	size_t GetAliensGridWidth() { return GetAliensGridHeight() == 0 ? 0 : aliens[0].size(); }
	size_t GetStartingAliensCount() { return GetAliensGridWidth() * GetAliensGridHeight(); }
	size_t GetDestroyedAliensCount() { return GetStartingAliensCount() - aliensCount; }

	void OnAlienMovedCallback(GameObject* alien, Direction moveDirection);
	void OnAlienDestroyedCallback(int xIndex, int yIndex);
	void OnAliensReachMargin();

	void MoveAliens(Direction dir, double speed);
};