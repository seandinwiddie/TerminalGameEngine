#pragma once
#include "Config.h"
#include "GridDirection.h"
#include "Singleton.h"
#include "ISimulationUpdatingEntity.h"
#include "Level.h"
#include "Event.h"

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
	double levelStartedTime = 0;

	SimulationPrinter* simulationPrinter;
	Level* level;
	vector<vector<GameObject*>> worldSpace;
	list<ISimulationUpdatingEntity*> entities;

	// move requests are sorted from slower to faster
	// slower objects have to move before faster ones to prevent false collisions detection
	list<MoveRequest> moveRequests;

//------------------------------------------------------------------------------------ Methods
public:
	void LoadLevel(Level* level);
	void Step();
	bool TryAddEntity(ISimulationUpdatingEntity* entity);
	void RequestMovement(GameObject* applicantObj, Direction moveDir, double moveSpeed);
	size_t GetWorldSizeX() const { return level->GetWorldSizeX(); }
	size_t GetWorldSizeY() const { return level->GetWorldSizeY(); }
	size_t GetScreenPadding() const { return level->GetScreenPadding(); }
	bool IsInsideGameSpaceX(int xPos) const;
	bool IsInsideGameSpaceY(int yPos) const;
	bool IsCoordinateInsideGameSpace(int xPos, int yPos) const;
	size_t GetScreenSizeX() const { return level->GetWorldSizeX() - 2 * level->GetScreenPadding(); }
	size_t GetScreenSizeY() const { return level->GetWorldSizeY() - 2 * level->GetScreenPadding(); }
	bool IsInsideScreenX(int xPos) const;
	bool IsInsideScreenY(int yPos) const;
	bool IsCoordinateInsideScreenSpace(int xPos, int yPos) const;
	const Level* GetActiveLevel() { return level; }
	void PrintGameOverWindow(const Frame& UIMessage);
	void SetTerminalHeader(const string& header);

private:
	void RemoveObject(GameObject* obj);
	bool TryMoveObjectAtDirection(GameObject* obj, Direction direction);
	void MoveObject(GameObject* obj, Direction direction);
	bool CanEntityBeAdded(const ISimulationUpdatingEntity* entity) const;
	bool IsEntityInSimulation(const ISimulationUpdatingEntity* newEntity) const;
	bool CanObjectMoveAtDirection(const GameObject* obj, Direction direction, GameObject*& outCollidingObject) const;
	void UpdateObjectCollisions(GameObject* collidingObj);
	bool IsWorldAreaEmpty(int startingY, int startingX, size_t width, size_t height) const;
	void ResetScreenManager(const string& backgroundFileName);
	void EnqueueMoveRequestSortingBySpeed(MoveRequest request);
	void UpdateAllEntities();
	void ExecuteMoveRequests();
	void UpdateAllObjectsCollisions();
	void PrintObjects();
	void WriteWorldSpace(GameObject* obj, bool insert);
};