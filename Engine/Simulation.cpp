#include "Simulation.h"
#include "Collider.h"
#include "SimulationPrinter.h"
#include "ISimulationEntity.h"
#include "GameObject.h"
#include "Level.h"
#include "TimeHelper.h"
#include "WorldSpace.h"
#include "DebugManager.h"
#include "UIPrinter.h"
#include "RandomUtils.h"
#include "Particle.h"

#include <Windows.h>
#include <cassert>
#include <stdexcept>

template<typename T> using uset = std::unordered_set<T>;

size_t Simulation::GetWorldSizeX() const { return level->GetWorldSizeX(); }
size_t Simulation::GetWorldSizeY() const { return level->GetWorldSizeY(); }
size_t Simulation::GetScreenPadding() const { return level->GetScreenPadding(); }
size_t Simulation::GetScreenSizeX() const { return level->GetWorldSizeX() - 2 * level->GetScreenPadding(); }
size_t Simulation::GetScreenSizeY() const { return level->GetWorldSizeY() - 2 * level->GetScreenPadding(); }
Level* Simulation::GetActiveLevel() { return level; }
UIPrinter& Simulation::GetUIPrinter() { return *uiPrinter; }

void Simulation::SpawnParticles
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
	std::optional<Direction> mainDirection
)
{
	int densityIntPart = static_cast<int>(density);
	double densityDecimalPart = density - densityIntPart;

	for (int y = posY; y < posY + height; ++y)
	{
		for (int x = posX; x < posX + width; ++x)
		{
			//add particles depending on density int part
			for (int density = 0; density <= densityIntPart; ++density)
			{
				//add particles depending on density fractional part
				if (density == densityIntPart && RandomUtils::GetRandomDouble(0, 1) > densityDecimalPart)
					continue;

				Particle* particle = new Particle(x, y, modelChar, color, speed, movementLifeTime, mainDirection);
				TryAddEntity(particle);
			}
		}
	}
}

void Simulation::Step()
{
	if (level->IsTerminated())
		return;

	if (level->IsPostGameOverPauseEnded())
	{
		level->Update();
		return;
	}

	moveRequests.clear();

	UpdateAllEntities();

	ExecuteMoveRequests();

	RemoveMarkedEntities();

	UpdateAllObjectsEndedCollisions();

	PrintObjects();

	OnFrameGenerated.Notify();

#if DEBUG_MODE && SHOW_FPS
	DebugManager::Instance().ShowAverageFPS();
#endif
}

void Simulation::RequestMovement(GameObject* applicantObj, Direction moveDir, double moveSpeed)
{
	if (IsEntityInSimulation(applicantObj) == false)
	{
		std::cerr << "object requesting movement but it's not in simulation";
		return;
	}

	MoveRequest request(applicantObj, moveDir, moveSpeed);
	EnqueueMoveRequestSortingBySpeed(request);
}

void Simulation::EnqueueMoveRequestSortingBySpeed(MoveRequest request)
{
	auto it = moveRequests.begin();
	while (it != moveRequests.end())
	{
		if (it->moveSpeed > request.moveSpeed)
			break;
		++it;
	}
	moveRequests.insert(it, request);
}

void Simulation::RemoveMarkedEntities()
{
	for (ISimulationEntity* entity : toRemoveEntities)
	{
		GameObject* objectEntity = dynamic_cast<GameObject*>(entity);
		if (objectEntity != nullptr)
		{
			objectEntity->OnDestroy();
			simulationPrinter->ClearObject(objectEntity);

			Collider* colliderEntity = dynamic_cast<Collider*>(entity);
			if(colliderEntity != nullptr)
				worldSpace.RemoveObject(colliderEntity);
			else
			{
				//todo: if a colliding object moves over a non colliding object, now it is not reprinted, improve in the future
				//if entity is not a collider and was covering other objects, they must be reprinted
				uset<Collider*> coveredObjects;
				if (!worldSpace.IsAreaEmpty(objectEntity->GetPosX(), objectEntity->GetPosY(), objectEntity->GetModelWidth(), objectEntity->GetModelHeight(), coveredObjects))
					for (Collider* elem : coveredObjects)
						elem->mustBeReprinted = true;
			}
		}
		entities.erase(entity);
		delete(entity);
	}
	toRemoveEntities.clear();
}

void Simulation::RemoveEntity(ISimulationEntity* entity)
{
	if (entity == nullptr)
		return;

	if (!IsEntityInSimulation(entity))
		return;

	//entity will be removed at proper stage of step
	toRemoveEntities.push_back(entity);
}

void Simulation::PrintObjects()
{
	//todo:if a colliding object and a non colliding object are in same tile, now there is no rule
	// to define which should be in front. for fast particles this is not a big problem, but in the future you may want to 
	//add a layer order system
	for (ISimulationEntity* entity : entities)
	{
		GameObject* objEntity = dynamic_cast<GameObject*>(entity);
		Particle* objParticle = nullptr;
		if (objEntity != nullptr && objEntity->mustBeReprinted)
		{
			objEntity->mustBeReprinted = false;
			simulationPrinter->PrintObject(objEntity);
		}
	}
}

void Simulation::UpdateAllEntities()
{
	level->Update();
	for (ISimulationEntity* entity : entities)
		entity->Update();
}

void Simulation::ExecuteMoveRequests()
{
	for (auto it = moveRequests.begin(); it != moveRequests.end(); ++it)
	{
		int oldXPos = it->object->GetPosX();
		int oldYPos = it->object->GetPosY();

		if (TryMoveObjectAtDirection(it->object, it->moveDir))
		{
			simulationPrinter->ClearArea(oldXPos, oldYPos, it->object->GetModelWidth(), it->object->GetModelHeight());
			it->object->mustBeReprinted = true;
		}
	}
}

void Simulation::UpdateAllObjectsEndedCollisions()
{
	for (auto entity : entities)
	{
		Collider* collider = dynamic_cast<Collider*>((entity));
		if (collider != nullptr)
			UpdateObjectEndedCollisions(collider);
	}
}

void Simulation::UpdateObjectEndedCollisions(Collider* collider)
{
	int xPos = collider->GetPosX();
	int yPos = collider->GetPosY();
	int xMax = collider->GetMaxPosX();
	int yMax = collider->GetMaxPosY();
	size_t width = collider->GetModelWidth();
	size_t height = collider->GetModelHeight();
	bool canExitScreen = collider->CanExitScreenSpace();

	//vector<bool> collisions(4);
	vector<uset<Collider*>> collisions (4);

	//screen collisions
	if (!canExitScreen && !IsCoordinateInsideScreenSpace(xPos, yMax + 1))
		collisions[Direction::up].insert(WorldSpace::SCREEN_MARGIN);
	if (!canExitScreen && !IsCoordinateInsideScreenSpace(xPos, yPos - 1))
		collisions[Direction::down].insert(WorldSpace::SCREEN_MARGIN);
	if(!canExitScreen && !IsCoordinateInsideScreenSpace(xMax + 1, yPos))
		collisions[Direction::right].insert(WorldSpace::SCREEN_MARGIN);
	if(!canExitScreen && !IsCoordinateInsideScreenSpace(xPos - 1, yPos))
		collisions[Direction::left].insert(WorldSpace::SCREEN_MARGIN);

	// object-object collisions
	worldSpace.IsAreaEmpty(xPos, yMax + 1, width, 1, collisions[Direction::up]);
	worldSpace.IsAreaEmpty(xPos, yPos - 1, width, 1, collisions[Direction::down]);
	worldSpace.IsAreaEmpty(xPos - 1, yPos, 1, height, collisions[Direction::left]);
	worldSpace.IsAreaEmpty(xMax + 1, yPos, 1, height, collisions[Direction::right]);
	
	collider->CALLED_BY_SIM_UpdateEndedCollisions(collisions);
} 

bool Simulation::TryAddEntity(ISimulationEntity* entity)
{
	GameObject* objectEntity = dynamic_cast<GameObject*>(entity);
	if (objectEntity != nullptr)
		objectEntity->Init();

	if (!CanEntityBeAdded(entity))
	{
		delete(entity);
		return false;
	}

	Collider* collider = dynamic_cast<Collider*>(entity);
	if (collider != nullptr)
		worldSpace.InsertObject(collider);

	entities.insert(entity);
	return true;
}

bool Simulation::CanEntityBeAdded(ISimulationEntity* entity) const
{
	if (IsEntityInSimulation(entity))
		return false;

	const Collider* collider = dynamic_cast<const Collider*>(entity);
	if (collider != nullptr)
	{
		return worldSpace.IsAreaEmpty
		(
			collider->GetPosX(), 
			collider->GetPosY(), 
			collider->GetModelWidth(),
			collider->GetModelHeight()
		);
	}
	else
		return true;
}

bool Simulation::IsEntityInSimulation(ISimulationEntity* newEntity) const
{
	auto it = entities.find(newEntity);
	return it != entities.end();
}

bool Simulation::TryMoveObjectAtDirection(GameObject* obj, Direction direction)
{
	uset<Collider*> outCollidingObjects;

	Collider* colliderObj = dynamic_cast<Collider*>(obj);

	if (worldSpace.CanObjectMoveAtDirection(obj, direction, outCollidingObjects) == false)
	{
		//remove entity if trying to move out of world space
		if (outCollidingObjects.find(WorldSpace::WORLD_MARGIN) != outCollidingObjects.end())
		{
			RemoveEntity(obj);
		}
		else
		{
			if (colliderObj != nullptr)
			{
				colliderObj->CALLED_BY_SIM_NotifyCollisionEnter(outCollidingObjects, direction);

				for (Collider* item : outCollidingObjects)
					if (item != WorldSpace::SCREEN_MARGIN)
						item->CALLED_BY_SIM_NotifyCollisionEnter(colliderObj, GetInverseDirection(direction));
			}
		}
		return false;
	}

	if(colliderObj != nullptr)
		worldSpace.MoveObject(colliderObj, direction);

	obj->CALLED_BY_SIM_Move(direction);

	return true;
}

void Simulation::LoadLevel (Level* level)
{
	this->level = level;

	for (ISimulationEntity* entity : entities)
		delete(entity);

	entities.clear();
	worldSpace.Init(level->GetWorldSizeX(), level->GetWorldSizeY(), level->GetScreenPadding());

#if DEBUG_MODE
	DebugManager::Instance().Reset(GetScreenSizeX(), GetScreenSizeY(), GetScreenPadding());
#endif
	
	ResetPrinters(level);
	level->LoadInSimulation();
}

void Simulation::ResetPrinters(const Level* level)
{
	Terminal::Instance().Clear();

	if (simulationPrinter != nullptr)
		delete(simulationPrinter);

	string s = level->GetBackgroundFileName();

	simulationPrinter = new SimulationPrinter
	(
		GetScreenSizeX(),
		GetScreenSizeY(),
		GetScreenPadding(), 
		level->GetBackgroundColor(),
		level->GetBackgroundFileName()
	);

	if (uiPrinter != nullptr)
		delete(uiPrinter);

	uiPrinter = new UIPrinter(GetScreenSizeX(), GetScreenSizeY(), GetScreenPadding(), level->GetMarginsColor());
}

bool Simulation::IsInsideScreenY(int yPos) const
{
	return
		yPos >= GetScreenPadding() &&
		yPos < GetWorldSizeY() - GetScreenPadding();
}
bool Simulation::IsInsideScreenX(int xPos) const
{
	return 
		xPos >= GetScreenPadding() &&
		xPos < GetWorldSizeX() - GetScreenPadding();
}