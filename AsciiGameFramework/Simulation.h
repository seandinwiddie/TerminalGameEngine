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

class ScreenManager;
class CollidingObject;

//------------------------------------------------------------------------------------ simulation
class Simulation : public Singleton<Simulation>
{
	//todo try to improve screen refresh

	friend class Singleton;
	friend class GameObject;
	friend class CollidingObject;

public:
	Event<> OnGameOver;
	Event<> OnGameStart;

private:
	const static int STEPS_PER_FRAME = 8;
	constexpr static float SHOW_GAMEOVER_SCREEN_AFTER_SECONDS = 1;
	constexpr static float ALLOW_PRESSING_KEY_TO_RESTART_GAME_AFTER_SECONDS = 1.5;
	const static int PREVENT_SCEEN_REFRESH_BEFORE_MILLISECONDS = 15;

	unsigned int worldSizeX;
	unsigned int worldSizeY;
	unsigned int screenPadding;
	bool isGameStarting = true;
	int printFrameStep;
	bool hasTerminated = false;
	double gameOverTime = -1;
	double runStartedTime = 0;

	ScreenManager* screenManager;
	std::vector<std::vector<CollidingObject*>> gameSpace;
	std::list<GameObject*> simulationObjects;


public:
	void Step();
	bool TryAddGameObject(GameObject* obj);
	bool TryMoveAtDirection(GameObject* obj, const Direction direction);
	void RemoveGameObject(GameObject* obj);
	bool HasTerminated() const { return hasTerminated; }
	void NotifyGameOver();
	void Reset(unsigned int worldSizeX, unsigned int worldSizeY, unsigned int screenPadding, const std::vector<string>& backgroundFileNames);
	double GetRunTime() const { return IsGameOver() ? gameOverTime - runStartedTime : TimeUtils::Instance().GetTime() - runStartedTime; }
	unsigned int GetWorldSizeX() const { return worldSizeX; }
	unsigned int GetWorldSizeY() const { return worldSizeY; }
	unsigned int GetScreenPadding() const { return screenPadding; }

private:
	bool CanObjectBeAdded(const GameObject* obj) const;
	bool IsInSimulation(const GameObject* obj) const;
	bool CanMoveAtDirection(const GameObject* obj, Direction direction, CollidingObject*& outCollidingObject) const;
	bool IsCoordinateInsideGameSpace(const int x, const int y) const;
	bool IsCoordinateInsideScreenSpace(const int x, const int y) const;

	bool IsGameOver() const { return gameOverTime > - 1; }
	bool IsShowGameoverDelayExpired() const;
	bool CanPlayerPressKeyToRestartGame() const;
	void UpdateObjectCollisionDirections(CollidingObject* collidingObj);
	bool IsSpaceEmpty(const int startingY, const int startingX, const int width, const int height) const;
	void ResetScreenManager(const std::vector<string>& backgroundFileNames);
};