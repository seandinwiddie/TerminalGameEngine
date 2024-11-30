#pragma once

#include "Config.h"
#include "WorldSpace.h"
#include "UIPrinter.h"
#include "SimulationPrinter.h"
#include <list>
#include <unordered_set>
#include <optional>
#include <memory>

namespace Engine
{
	using string = std::string;
	template<typename T> using list = std::list<T>;
	template<typename T> using uset = std::unordered_set<T>;
	template<typename T> using unique_ptr = std::unique_ptr<T>;
	template<typename T> using shared_ptr = std::shared_ptr<T>;

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
		friend class Singleton;
		friend class GameObject;

		//------------------------------------------------------------------------------------ Structs
		struct MoveRequest
		{
			shared_ptr<GameObject> object;
			Direction moveDir;
			double moveSpeed;

			MoveRequest(shared_ptr<GameObject> object, Direction direction, double speed)
				:object(object), moveDir(direction), moveSpeed(speed){ }
		};

		//------------------------------------------------------------------------------------ Fields
	public:
		Event<> OnFrameGenerated;

	private:
		unique_ptr<SimulationPrinter> simulationPrinter;
		unique_ptr<UIPrinter> uiPrinter;
		shared_ptr<Level> level;
		WorldSpace worldSpace;
		uset<shared_ptr<ISimulationEntity>> entities;
		list<shared_ptr<ISimulationEntity>> toRemoveEntities;

		// move requests are sorted from slower to faster
		// slower objects have to move before faster ones to prevent false collisions detection
		list<MoveRequest> moveRequests;

		//------------------------------------------------------------------------------------ Methods
	public:
		void LoadLevel(shared_ptr<Level> level);
		void Step();
		bool TryAddEntity(shared_ptr<ISimulationEntity> entity);
		void RemoveEntity(shared_ptr<ISimulationEntity> entity);
		void RequestMovement(shared_ptr<GameObject> applicantObj, Direction moveDir, double moveSpeed);
		size_t GetWorldSizeX() const;
		size_t GetWorldSizeY() const;
		size_t GetScreenPadding() const;
		size_t GetScreenSizeX() const;
		size_t GetScreenSizeY() const;
		shared_ptr<Level> GetActiveLevel();
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
		bool TryMoveObjectAtDirection(shared_ptr<GameObject> obj, Direction direction);
		bool CanEntityBeAdded(shared_ptr<ISimulationEntity> entity) const;
		bool IsEntityInSimulation(shared_ptr<ISimulationEntity> newEntity) const;
		void UpdateObjectEndedCollisions(shared_ptr<Collider> collidingObj);
		void ResetPrinters(shared_ptr<const Level> level);
		void EnqueueMoveRequestSortingBySpeed(MoveRequest request);
		void UpdateAllEntities();
		void ExecuteMoveRequests();
		void UpdateAllObjectsEndedCollisions();
		void PrintObjects();
		void RemoveMarkedEntities();

		bool IsInsideScreenX(int xPos) const;
		bool IsInsideScreenY(int yPos) const;
		bool IsCoordinateInsideScreenSpace(int xPos, int yPos) const { return IsInsideScreenX(xPos) && IsInsideScreenY(yPos); }

		void MarkAreaToReprint(shared_ptr<GameObject> objArea);
		void MarkAreaToReprintAfterMovement(shared_ptr<GameObject> obj, int oldPosX, int oldPosY);
		void UnmarkObjectToReprint(shared_ptr<GameObject> obj) { obj->mustBeReprinted = false; }
	};
}
