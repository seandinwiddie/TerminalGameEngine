#pragma once
#include "Config.h"
#include "GridDirection.h"
#include "Singleton.h"
#include "ISimulationUpdatingEntity.h"
#include "Level.h"

#include <list>
#include <vector>

using namespace GridDirection;
using string = std::string;

//class Level;
class CollidingObject;
class ISimulationUpdatingEntity;
class Frame;
class SimulationPrinter;

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
	constexpr static float PREVENT_REFRESHING_FRAME_BEFORE_MILLISECONDS = 4;


//------------------------------------------------------------------------------------ Fields
	uint printFrameStep;
	double levelStartedTime = 0;
	float lastTimePrintedFrame = -1; //todo use double for time

	SimulationPrinter* simulationPrinter;
	Level* level;

	std::vector<std::vector<CollidingObject*>> gameSpace;
	std::list<ISimulationUpdatingEntity*> objects;
	std::list<MoveRequest> moveRequests;
	std::list<ISimulationUpdatingEntity*> updatingEntities;
//------------------------------------------------------------------------------------ Methods
public:
	void Step();
	bool TryAddObject(GameObject* obj);
	void RequestMovement(GameObject* applicantObj, Direction direction, float speed);
	void RemoveObject(GameObject* obj);

	uint GetWorldSizeX() const { return level->GetWorldSizeX(); }
	uint GetWorldSizeY() const { return level->GetWorldSizeY(); }
	uint GetScreenPadding() const { return level->GetScreenPadding(); }

	bool IsInsideGameSpaceX(int xPos) const;
	bool IsInsideGameSpaceY(int yPos) const;
	bool IsCoordinateInsideGameSpace(int xPos, int yPos) const;
	
	uint GetScreenSizeX() const { return level->GetWorldSizeX() - 2 * level->GetScreenPadding(); }
	uint GetScreenSizeY() const { return level->GetWorldSizeY() - 2 * level->GetScreenPadding(); }

	bool IsInsideScreenX(int xPos) const;
	bool IsInsideScreenY(int yPos) const;
	bool IsCoordinateInsideScreenSpace(int xPos, int yPos) const;

	const Level* GetActiveLevel() { return level; }

	void ShowUIFrame(const Frame& UIMessage);
	void AddUpdatable(ISimulationUpdatingEntity* updatable);

	void SetTerminalHeader(const string& header);

	void Reset
	(
		Level* level,
		uint worldSizeX,
		uint worldSizeY,
		uint screenPadding,
		const std::vector<string>& backgroundFileNames
	);

private:
	bool TryMoveObjectAtDirection(GameObject* obj, Direction direction);
	void MoveObject(GameObject* obj, Direction direction);
	bool CanObjectBeAdded(const GameObject* obj) const;
	bool IsObjectInSimulation(const ISimulationUpdatingEntity* obj) const;
	bool CanObjectMoveAtDirection(const GameObject* obj, Direction direction, CollidingObject*& outCollidingObject) const;
	void UpdateObjectCollisionDirections(CollidingObject* collidingObj);

	bool IsSpaceEmpty(uint startingY, uint startingX, uint width, uint height) const;
	void ResetScreenManager(const std::vector<string>& backgroundFileNames);

};