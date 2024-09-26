#pragma once
#include "Config.h"
#include "GridDirection.h"
#include "Singleton.h"
#include "ISimulationUpdatingEntity.h"
#include "Level.h"
#include "Event.h"
#include "WorldSpace.h"
#include "SimulationPrinter.h"
#include "UIPrinter.h"
#include "DebugPrinter.h"

#include <list>
#include <vector>

using namespace GridDirection;
using string = std::string;
template<typename T> using vector = std::vector<T>;
template<typename T> using list = std::list<T>;

class GameObject;
class ISimulationUpdatingEntity;
class Frame;
class SimulationPrinter;

class Simulation : public Singleton<Simulation>
{
friend class Singleton;
friend class GameObject;

	struct MoveRequest
	{
		GameObject* object;
		Direction moveDir;
		double moveSpeed;

		MoveRequest(GameObject* object, Direction direction, double speed)
			:object(object),moveDir(direction), moveSpeed(speed){}
	};

//------------------------------------------------------------------------------------ Fields
public:
	Event<> OnFrameGenerated;

private:
	SimulationPrinter* simulationPrinter;
	UIPrinter* uiPrinter;

	Level* level;

	WorldSpace worldSpace;
	list<ISimulationUpdatingEntity*> entities;

	// move requests are sorted from slower to faster
	// slower objects have to move before faster ones to prevent false collisions detection
	list<MoveRequest> moveRequests;

//------------------------------------------------------------------------------------ Methods
public:
	void LoadLevel(Level* level);
	void Step();
	bool TryAddEntity(ISimulationUpdatingEntity* entity);
	void RemoveEntity(ISimulationUpdatingEntity* obj);
	void RequestMovement(GameObject* applicantObj, Direction moveDir, double moveSpeed);
	size_t GetWorldSizeX() const { return level->GetWorldSizeX(); }
	size_t GetWorldSizeY() const { return level->GetWorldSizeY(); }
	size_t GetScreenPadding() const { return level->GetScreenPadding(); }
	size_t GetScreenSizeX() const { return level->GetWorldSizeX() - 2 * level->GetScreenPadding(); }
	size_t GetScreenSizeY() const { return level->GetWorldSizeY() - 2 * level->GetScreenPadding(); }
	Level* GetActiveLevel() { return level; }

	UIPrinter& GetUIPrinter() { return *uiPrinter; }

private:
	bool TryMoveObjectAtDirection(GameObject* obj, Direction direction);
	bool CanEntityBeAdded(const ISimulationUpdatingEntity* entity) const;
	bool IsEntityInSimulation(const ISimulationUpdatingEntity* newEntity) const;
	void UpdateObjectEndedCollisions(GameObject* collidingObj);
	void ResetPrinters(const Level* level);
	void EnqueueMoveRequestSortingBySpeed(MoveRequest request);
	void UpdateAllEntities();
	void ExecuteMoveRequests();
	void UpdateAllObjectsEndedCollisions();
	void PrintObjects();

	bool IsInsideScreenX(int xPos) const;
	bool IsInsideScreenY(int yPos) const;
	bool IsCoordinateInsideScreenSpace(int xPos, int yPos) const { return IsInsideScreenX(xPos) && IsInsideScreenY(yPos); }
};