#pragma once

#include "Config.h"
#include "GridDirection.h"
#include "Singleton.h"
#include <list>
#include <vector>
#include <string>
#include <tuple>

using namespace GridDirection;
using string = std::string;

class Level;
class SimulationPrinter;
class CollidingObject;
class SimulationObject;
class Frame;

class Simulation : public Singleton<Simulation>
{
	friend class Singleton;
	friend class TransformObject;
	friend class CollidingObject;

	struct MoveRequest
	{
		TransformObject* object;
		Direction direction;
		float speed;

		MoveRequest(TransformObject* object, Direction direction, float speed)
			:object(object),direction(direction), speed(speed){}
	};

//------------------------------------------------------------------------------------ Settings
private:
	const static uint STEPS_PER_FRAME = 8;

//------------------------------------------------------------------------------------ Fields

	uint worldSizeX;
	uint worldSizeY;
	uint screenPadding;
	uint printFrameStep;
	double levelStartedTime = 0;

	SimulationPrinter* simulationPrinter;
	Level* level;

	std::vector<std::vector<CollidingObject*>> gameSpace;
	std::list<SimulationObject*> simulationObjects;
	std::list<MoveRequest> moveRequests;
//------------------------------------------------------------------------------------ Methods
public:
	void Step();
	bool TryAddGameObject(TransformObject* obj);
	void RequestDiscreteMovement(TransformObject* obj, Direction direction, float speed);
	void RemoveGameObject(TransformObject* obj);

	uint GetWorldSizeX() const { return worldSizeX; }
	uint GetWorldSizeY() const { return worldSizeY; }
	uint GetScreenPadding() const { return screenPadding; }
	
	bool IsInsideScreenX(int xPos) const;
	bool IsInsideScreenY(int yPos) const;
	bool IsCoordinateInsideScreenSpace(int xPos, int yPos) const;
	uint GetScreenSizeX() const { return worldSizeX - 2 * screenPadding; }
	uint GetScreenSizeY() const { return worldSizeY - 2 * screenPadding; }

	bool IsInsideGameSpaceX(int xPos) const;
	bool IsInsideGameSpaceY(int yPos) const;
	bool IsCoordinateInsideGameSpace(int xPos, int yPos) const;

	const Level* GetActiveLevel() { return level; }

	void ShowUIFrame(const Frame& UIMessage);

	void Reset
	(
		Level* level,
		uint worldSizeX,
		uint worldSizeY,
		uint screenPadding,
		bool showLevelTime,
		const std::vector<string>& backgroundFileNames
	);

private:
	bool TryMoveAtDirection(TransformObject* obj, Direction direction);
	bool CanObjectBeAdded(const TransformObject* obj) const;
	bool IsInSimulation(const SimulationObject* obj) const;
	bool CanMoveAtDirection(const TransformObject* obj, Direction direction, CollidingObject*& outCollidingObject) const;
	
	void UpdateObjectCollisionDirections(CollidingObject* collidingObj);
	bool IsSpaceEmpty(uint startingY, uint startingX, uint width, uint height) const;
	void ResetScreenManager(bool showLevelTime, const std::vector<string>& backgroundFileNames);
};