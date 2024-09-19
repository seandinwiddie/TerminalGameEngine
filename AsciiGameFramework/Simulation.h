#pragma once

#include "Config.h"
#include "GridDirection.h"
#include "Singleton.h"
#include <list>
#include <vector>

using namespace GridDirection;
using string = std::string;

class Level;
class SimulationPrinter;
class CollidingObject;
class ISimulationUpdatable;
class Frame;

class Simulation : public Singleton<Simulation>
{
	friend class Singleton;
	friend class GameObject;
	friend class CollidingObject;

	struct MoveRequest
	{
		GameObject* object;
		Direction direction;
		float speed;

		MoveRequest(GameObject* object, Direction direction, float speed)
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
	std::list<ISimulationUpdatable*> simulationObjects;
	std::list<MoveRequest> moveRequests;
//------------------------------------------------------------------------------------ Methods
public:
	void Step();
	bool TryAddObject(GameObject* obj);
	void RequestMovement(GameObject* obj, Direction direction, float speed);
	void RemoveObject(GameObject* obj);

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

	bool TryMoveAtDirection(GameObject* obj, Direction direction);
	bool CanObjectBeAdded(const GameObject* obj) const;
	bool IsInSimulation(const ISimulationUpdatable* obj) const;
	bool CanMoveAtDirection(const GameObject* obj, Direction direction, CollidingObject*& outCollidingObject) const;
	
	void UpdateObjectCollisionDirections(CollidingObject* collidingObj);
	bool IsSpaceEmpty(uint startingY, uint startingX, uint width, uint height) const;
	void ResetScreenManager(bool showLevelTime, const std::vector<string>& backgroundFileNames);
	void MoveObject(GameObject* obj, Direction direction);
};