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
			GameObject* object;
			Direction moveDir;
			double moveSpeed;

			MoveRequest(GameObject* object, Direction direction, double speed)
				:object(object), moveDir(direction), moveSpeed(speed){ }
		};

		//------------------------------------------------------------------------------------ Fields
	public:
		Event<> OnFrameGenerated;

	private:
		unique_ptr<SimulationPrinter> simulationPrinter;
		unique_ptr<UIPrinter> uiPrinter;
		Level* level;
		WorldSpace worldSpace;
		uset<ISimulationEntity*> entities;
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
		bool CanEntityBeAdded(ISimulationEntity* entity) const;
		bool IsEntityInSimulation(ISimulationEntity* newEntity) const;
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

		void MarkObjectsInAreaToReprint(GameObject* objArea);
		void MarkObjectToReprint(GameObject* obj);
		void MarkObjectToReprintAfterMovement(GameObject* obj, int oldPosX, int oldPosY);
		void UnmarkObjectToReprint(GameObject* obj) { obj->mustBeReprinted = false; }
	};
}
