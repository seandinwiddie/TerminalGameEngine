#pragma once

#include "Config.h"
#include "WorldSpace.h"

#include <list>
#include <vector>
#include <optional>

using namespace GridDirection;
using string = std::string;
template<typename T> using vector = std::vector<T>;
template<typename T> using list = std::list<T>;

class Collider;
class GameObject;
class ISimulationEntity;
class Frame;
class SimulationPrinter;
class UIPrinter;
class Level;

class Simulation : public Singleton<Simulation>
{
//------------------------------------------------------------------------------------ Friend Classes
friend class Singleton; //todo remove
friend class Collider;
friend class GameObject;

//------------------------------------------------------------------------------------ Structs
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
	list<ISimulationEntity*> entities;
	list<ISimulationEntity*> toRemoveEntities;

	// move requests are sorted from slower to faster
	// slower objects have to move before faster ones to prevent false collisions detection
	list<MoveRequest> moveRequests;

//------------------------------------------------------------------------------------ Methods
public:
	void LoadLevel(Level* level);
	void Step();
	bool TryAddEntity(ISimulationEntity* entity);
	void RemoveEntity(ISimulationEntity* entity);
	void RequestMovement(GameObject* applicantObj, Direction moveDir, double moveSpeed);
	size_t GetWorldSizeX() const;
	size_t GetWorldSizeY() const;
	size_t GetScreenPadding() const;
	size_t GetScreenSizeX() const;
	size_t GetScreenSizeY() const;
	Level* GetActiveLevel();
	UIPrinter& GetUIPrinter();

	void SpawnParticles
	(
		int posX, 
		int posY, 
		size_t width, 
		size_t height, 
		char modelChar, 
		int color,
		double speed, 
		size_t movementLifeTime,
		double density,
		std::optional<Direction> mainDirection = std::nullopt
	);

private:
	bool TryMoveObjectAtDirection(GameObject* obj, Direction direction);
	bool CanEntityBeAdded(const ISimulationEntity* entity) const;
	bool IsEntityInSimulation(const ISimulationEntity* newEntity) const;
	void UpdateObjectEndedCollisions(Collider* collidingObj);
	void ResetPrinters(const Level* level);
	void EnqueueMoveRequestSortingBySpeed(MoveRequest request);
	void UpdateAllEntities();
	void ExecuteMoveRequests();
	void UpdateAllObjectsEndedCollisions();
	void PrintObjects();
	void RemoveMarkedEntities();

	bool IsInsideScreenX(int xPos) const;
	bool IsInsideScreenY(int yPos) const;
	bool IsCoordinateInsideScreenSpace(int xPos, int yPos) const { return IsInsideScreenX(xPos) && IsInsideScreenY(yPos); }
};