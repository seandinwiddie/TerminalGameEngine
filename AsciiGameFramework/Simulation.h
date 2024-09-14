#pragma once

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>
#include <stdexcept>
#include <random>
#include "InputUtils.h"
#include "Time.h"
#include "RandomUtils.h"
#include "AudioManager.h"
#include "Persistence.h"
#include "GridDirection.h"
#include "Singleton.h"
#include "GameObject.h"
#include "Event.h"


using namespace GridDirection;
using string = std::string;

const class Level;
class ScreenManager;
class CollidingObject;

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
	bool hasTerminated = false;

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
	bool HasTerminated() const { return hasTerminated; }
	void Terminate();
	//double GetLevelTime() const;
	unsigned int GetWorldSizeX() const { return worldSizeX; }
	unsigned int GetWorldSizeY() const { return worldSizeY; }
	unsigned int GetScreenPadding() const { return screenPadding; }
	bool IsShowingGameOverScreen() const;
	void ShowGameOverScreen(const int score, const int bestScore);
	const Level* const GetLevel() { return level; }

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


	bool IsShowGameoverDelayExpired() const;
	bool CanPlayerPressKeyToRestartGame() const;
	void UpdateObjectCollisionDirections(CollidingObject* collidingObj);
	bool IsSpaceEmpty(const int startingY, const int startingX, const int width, const int height) const;
	void ResetScreenManager(bool showLevelTime, const std::vector<string>& backgroundFileNames);
};