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
		Direction direction;
		double speed;

		MoveRequest(GameObject* object, Direction direction, double speed)
			:object(object),direction(direction), speed(speed){}
	};

//------------------------------------------------------------------------------------ Fields
	double levelStartedTime = 0;
	double lastTimePrintedFrame = -1;

	SimulationPrinter* simulationPrinter;
	Level* level;

	vector<vector<GameObject*>> worldSpace;
	list<ISimulationUpdatingEntity*> entities;
	list<MoveRequest> moveRequests;

//------------------------------------------------------------------------------------ Methods
public:
	void LoadLevel(Level* level);
	void Step();
	bool TryAddEntity(ISimulationUpdatingEntity* obj);
	void RequestMovement(GameObject* applicantObj, Direction direction, double speed);
	void RemoveObject(GameObject* obj);
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
	bool TryMoveObjectAtDirection(GameObject* obj, Direction direction);
	void MoveObject(GameObject* obj, Direction direction);
	bool CanObjectBeAdded(const GameObject* obj) const;
	bool IsObjectInSimulation(const ISimulationUpdatingEntity* obj) const;
	bool CanObjectMoveAtDirection(const GameObject* obj, Direction direction, GameObject*& outCollidingObject) const;
	void UpdateObjectcollisionDirs(GameObject* collidingObj);
	bool IsSpaceEmpty(int startingY, int startingX, size_t width, size_t height) const;
	void ResetScreenManager(const string& backgroundFileName);

};