#pragma once

#include "GridDirection.h"
#include "Singleton.h"
#include <list>
#include <vector>
#include <string>

using namespace GridDirection;
using string = std::string;

const class Level;
class ScreenManager;
class CollidingObject;
class SimulationObject;

//------------------------------------------------------------------------------------ simulation
class Simulation : public Singleton<Simulation>
{
	friend class Singleton;
	friend class TransformObject;
	friend class CollidingObject;

private:
	const static int STEPS_PER_FRAME = 8;
	const static int PREVENT_SCEEN_REFRESH_BEFORE_MILLISECONDS = 15;

	unsigned int worldSizeX;
	unsigned int worldSizeY;
	unsigned int screenPadding;
	int printFrameStep;

	double levelStartedTime = 0;

	ScreenManager* screenManager;
	std::vector<std::vector<CollidingObject*>> gameSpace;
	std::list<SimulationObject*> simulationObjects;
	Level* level;

public:
	void Step();
	bool TryAddGameObject(TransformObject* obj);
	bool TryMoveAtDirection(TransformObject* obj, const Direction direction);
	void RemoveGameObject(TransformObject* obj);

	//double GetLevelTime() const;
	unsigned int GetWorldSizeX() const { return worldSizeX; }
	unsigned int GetWorldSizeY() const { return worldSizeY; }
	unsigned int GetScreenPadding() const { return screenPadding; }
	const Level* const GetLevel() { return level; }
	ScreenManager* GetScreenManager() { return screenManager; }

	void Reset
	(
		Level* level,
		const unsigned int worldSizeX,
		const unsigned int worldSizeY,
		const unsigned int screenPadding,
		const bool showLevelTime,
		const std::vector<string>& backgroundFileNames
	);

private:
	bool CanObjectBeAdded(const TransformObject* obj) const;
	bool IsInSimulation(const TransformObject* obj) const;
	bool CanMoveAtDirection(const TransformObject* obj, Direction direction, CollidingObject*& outCollidingObject) const;
	bool IsCoordinateInsideGameSpace(const int x, const int y) const;
	bool IsCoordinateInsideScreenSpace(const int x, const int y) const;
	void UpdateObjectCollisionDirections(CollidingObject* collidingObj);
	bool IsSpaceEmpty(const int startingY, const int startingX, const int width, const int height) const;
	void ResetScreenManager(bool showLevelTime, const std::vector<string>& backgroundFileNames);
};