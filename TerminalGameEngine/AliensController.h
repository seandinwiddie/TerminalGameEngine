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
	double const BASE_MOVE_SPEED = 1;

	const double ALL_ALIENS_ELIMINATED_SPEED_INCREASE = 4;

	const double HARDEST_WAVE_SPEED_INCREASE = 4;
	const double MAX_SPEED_WAVE = 5;
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

//------------------------------------------------------------------- Methods
public:
	AliensController(SpaceInvadersLevel* level, int aliensCountX, int aliensCountY);
	void Update() override;
	void RegisterAlien(Alien* alien, int xPos, int yPos);

private:
	//double GetMoveDelay();
	double GetSpeedX()const;
	double GetEliminatedAliensSpeedBoost() const;
	double GetWaveSpeedBoost() const;

	size_t GetAliensGridHeight() const { return aliens.size(); }
	size_t GetAliensGridWidth() const { return GetAliensGridHeight() == 0 ? 0 : aliens[0].size(); }
	size_t GetStartingAliensCount() const { return GetAliensGridWidth() * GetAliensGridHeight(); }
	size_t GetDestroyedAliensCount() const { return GetStartingAliensCount() - aliensCount; }

	void OnAlienMovedCallback(GameObject* alien, Direction moveDirection);
	void OnAlienDestroyedCallback(int xIndex, int yIndex);
	void OnAliensReachMargin();

	void MoveAliens(Direction dir, double speed);
};