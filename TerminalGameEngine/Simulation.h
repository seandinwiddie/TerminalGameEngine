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
class GameObject;
class ISimulationUpdatingEntity;
class Frame;
class SimulationPrinter;
class ISimulationUpdatingEntity;

class Simulation : public Singleton<Simulation>
{
	friend class Singleton;
	friend class GameObject;

	struct MoveRequest
	{
		GameObject* object;
		Direction direction;
		double speed;

		MoveRequest(GameObject* object, Direction direction, double speed)
			:object(object),direction(direction), speed(speed){}
	};

//------------------------------------------------------------------------------------ Fields
	double levelStartedTime = 0;
	double lastTimePrintedFrame = -1; //todo use double for time

	SimulationPrinter* simulationPrinter;
	Level* level;

	std::vector<std::vector<GameObject*>> worldSpace;
	std::list<ISimulationUpdatingEntity*> entities;
	std::list<MoveRequest> moveRequests;
//------------------------------------------------------------------------------------ Methods
public:
	void LoadLevel(Level* level);
	void Step();
	bool TryAddEntity(ISimulationUpdatingEntity* obj);
	void RequestMovement(GameObject* applicantObj, Direction direction, double speed);
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

	void PrintGameOverWindow(const Frame& UIMessage);

	void SetTerminalHeader(const string& header);

private:
	bool TryMoveObjectAtDirection(GameObject* obj, Direction direction);
	void MoveObject(GameObject* obj, Direction direction);
	bool CanObjectBeAdded(const GameObject* obj) const;
	bool IsObjectInSimulation(const ISimulationUpdatingEntity* obj) const;
	bool CanObjectMoveAtDirection(const GameObject* obj, Direction direction, GameObject*& outCollidingObject) const;
	void UpdateObjectCollisionDirections(GameObject* collidingObj);

	bool IsSpaceEmpty(uint startingY, uint startingX, uint width, uint height) const;
	void ResetScreenManager(const string& backgroundFileName);

};