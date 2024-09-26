#pragma once
#include "ISimulationEntity.h"
#include "GridDirection.h"
#include <vector>

template <typename T> using vector = std::vector<T>;
using namespace GridDirection;

class Alien;
class Level;
class GameObject;

class AliensController : public ISimulationEntity
{
//------------------------------------------------------------------- Settings

//------------------------------------------------------------------- Fields
private:
	// references
	Level* level;
	vector<vector<Alien*>> aliens;
	
	// state
	size_t aliensCount;
	size_t aliensPosX;
	Direction xMoveDirection = Direction::right;
	bool isTimeToMoveAliensDown = false;
	double lastTimeMoved = -1;

//------------------------------------------------------------------- Methods
public:
	AliensController(Level* level, int aliensCountX, int aliensCountY);
	void Update() override;
	void RegisterAlien(Alien* alien, int xPos, int yPos);

private:
	double GetMoveDelay(){ return 1; }
	size_t GetAliensGridHeight() { return aliens.size(); }
	size_t GetAliensGridWidth() { return GetAliensGridHeight() == 0 ? 0 : aliens[0].size(); }

	void OnAlienMovedCallback(GameObject* alien, Direction moveDirection);
	void OnAliensReachMargin();

	void MoveAliens(Direction dir, double speed);
};