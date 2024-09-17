#pragma once

#include "Config.h"
#include "GridDirection.h"
#include "Singleton.h"
#include <list>
#include <vector>
#include <string>

using namespace GridDirection;
using string = std::string;

class Level;
class ScreenManager;
class CollidingObject;
class SimulationObject;

class Simulation : public Singleton<Simulation>
{
	friend class Singleton;
	friend class TransformObject;
	friend class CollidingObject;
//------------------------------------------------------------------------------------ Settings
private:
	const static uint STEPS_PER_FRAME = 8;
	const static uint PREVENT_SCEEN_REFRESH_BEFORE_MILLISECONDS = 15;

//------------------------------------------------------------------------------------ Fields
	uint worldSizeX;
	uint worldSizeY;
	uint screenPadding;
	uint printFrameStep;
	double levelStartedTime = 0;
	ScreenManager* screenManager;
	std::vector<std::vector<CollidingObject*>> gameSpace;
	std::list<SimulationObject*> simulationObjects;
	Level* level;

//------------------------------------------------------------------------------------ Methods
public:
	void Step();
	bool TryAddGameObject(TransformObject* obj);
	bool TryMoveAtDirection(TransformObject* obj, const Direction direction);
	void RemoveGameObject(TransformObject* obj);

	uint GetWorldSizeX() const { return worldSizeX; }
	uint GetWorldSizeY() const { return worldSizeY; }
	uint GetScreenPadding() const { return screenPadding; }
	
	bool IsInsideScreenX(const int xPos) const;
	bool IsInsideScreenY(const int yPos) const;
	bool IsCoordinateInsideScreenSpace(const int xPos, const int yPos) const;

	bool IsInsideGameSpaceX(const int xPos) const;
	bool IsInsideGameSpaceY(const int yPos) const;
	bool IsCoordinateInsideGameSpace(const int xPos, const int yPos) const;

	const Level* const GetLevel() { return level; }
	ScreenManager* GetScreenManager() { return screenManager; }

	void Reset
	(
		Level* level,
		const uint worldSizeX,
		const uint worldSizeY,
		const uint screenPadding,
		const bool showLevelTime,
		const std::vector<string>& backgroundFileNames
	);

private:
	bool CanObjectBeAdded(const TransformObject* obj) const;
	bool IsInSimulation(const SimulationObject* obj) const;
	bool CanMoveAtDirection(const TransformObject* obj, Direction direction, CollidingObject*& outCollidingObject) const;
	
	void UpdateObjectCollisionDirections(CollidingObject* collidingObj);
	bool IsSpaceEmpty(const uint startingY, const uint startingX, const uint width, const uint height) const;
	void ResetScreenManager(bool showLevelTime, const std::vector<string>& backgroundFileNames);
};