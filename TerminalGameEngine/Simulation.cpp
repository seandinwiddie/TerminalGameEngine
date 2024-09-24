#include "Simulation.h"
#include "GameObject.h"
#include "SimulationPrinter.h"
#include "ISimulationUpdatingEntity.h"
#include "GameObject.h"
#include "Level.h"
#include "TimeHelper.h"
#include "WorldSpace.h"

#include <Windows.h>
#include <cassert>
#include <stdexcept>

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

void Simulation::Step()
{
	//todo polish this
	//---------------- prevent step
	if (level->IsTerminated())
		return;

	if (level->IsPostGameOverPauseEnded())
	{
		level->Update();
		return;
	}	

	//---------------- 
	moveRequests.clear();

	UpdateAllEntities();

	ExecuteMoveRequests();

	UpdateAllObjectsCollisions();

	PrintObjects();
	
	OnFrameGenerated.Notify();

#if DEBUG_MODE && SHOW_FPS
	simulationPrinter->DEBUG_PrintAverageFps();
#endif
}

void Simulation::PrintObjects()
{
	for (ISimulationUpdatingEntity* updatingEntity : entities)
	{
		GameObject* obj = dynamic_cast<GameObject*>(updatingEntity);
		if (obj != nullptr && obj->mustBeReprinted)
		{
			obj->mustBeReprinted = false;
			simulationPrinter->PrintObject(obj);
		}
}
}

void Simulation::UpdateAllEntities()
{
	level->Update();
	for (ISimulationUpdatingEntity* entity : entities)
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

void Simulation::UpdateAllObjectsCollisions()
{
	for (auto it = entities.rbegin(); it != entities.rend(); ++it)
	{
		GameObject* obj = dynamic_cast<GameObject*>((*it));
		if (obj != nullptr)
			UpdateObjectCollisions(obj);
	}
}

void Simulation::UpdateObjectCollisions(GameObject* obj)
{
	int xPos = obj->GetPosX();
	int yPos = obj->GetPosY();
	int xMax = obj->GetMaxPosX();
	int yMax = obj->GetMaxPosY();
	size_t width = obj->GetModelWidth();
	size_t height = obj->GetModelHeight();
	bool canExitScreen = obj->CanExitScreenSpace();

	vector<bool> collisions(4);

	// object - screen margin collisions
	collisions[Direction::up] = !canExitScreen && !IsCoordinateInsideScreenSpace(xPos, yMax + 1);
	collisions[Direction::down] = !canExitScreen && !IsCoordinateInsideScreenSpace(xPos, yPos - 1);
	collisions[Direction::right] = !canExitScreen && !IsCoordinateInsideScreenSpace(xMax + 1, yPos);
	collisions[Direction::left] = !canExitScreen && !IsCoordinateInsideScreenSpace(xPos - 1, yPos);

	// object-object collisions
	if(collisions[Direction::up] == false)
		collisions[Direction::up] = !worldSpace.IsAreaEmpty(xPos, yMax + 1, width, 1);

	if (collisions[Direction::down] == false)
		collisions[Direction::down] = !worldSpace.IsAreaEmpty(xPos, yPos - 1, width, 1);

	if (collisions[Direction::left] == false)
		collisions[Direction::left] = !worldSpace.IsAreaEmpty(xPos - 1, yPos, 1, height);

	if (collisions[Direction::right] == false)
		collisions[Direction::right] = !worldSpace.IsAreaEmpty(xMax + 1, yPos, 1, height);

	obj->CALLED_BY_SIM_NotifyCollisionsExit(collisions);
} 

bool Simulation::TryAddEntity(ISimulationUpdatingEntity* entity)
{
	GameObject* objEntity = dynamic_cast<GameObject*>(entity);
	if (objEntity != nullptr)
		objEntity->Init();

	if (!CanEntityBeAdded(entity))
	{
		delete(entity);
		return false;
	}
	
	if (objEntity != nullptr)
		worldSpace.InsertObject(objEntity);

	entities.push_back(entity);
	return true;
}

bool Simulation::CanEntityBeAdded(const ISimulationUpdatingEntity* entity) const
{
	if (IsEntityInSimulation(entity))
		return false;

	const GameObject* objEntity = dynamic_cast<const GameObject*>(entity);
	if (objEntity != nullptr)
		return worldSpace.IsAreaEmpty(objEntity->GetPosX(), objEntity->GetPosY(), objEntity->GetModelWidth(), objEntity->GetModelHeight());
	else
		return true;
}

bool Simulation::IsEntityInSimulation(const ISimulationUpdatingEntity* newEntity) const
{
	for (ISimulationUpdatingEntity* entity : entities)
		if (newEntity == entity)
			return true;

	return false;
}

bool Simulation::TryMoveObjectAtDirection(GameObject* obj, Direction direction)
{
	GameObject* outOtherObj;

	if (worldSpace.CanObjectMoveAtDirection(obj, direction, outOtherObj) == false)
	{
		if (outOtherObj == WorldSpace::WORLD_MARGIN)
		{
			RemoveObject(obj);
		}
		else if (outOtherObj == WorldSpace::SCREEN_MARGIN)
		{
			obj->CALLED_BY_SIM_NotifyCollisionEnter(nullptr, direction);
		}
		else
		{
			obj->CALLED_BY_SIM_NotifyCollisionEnter(outOtherObj, direction);
			outOtherObj->CALLED_BY_SIM_NotifyCollisionEnter(obj, GetInverseDirection(direction));
		}

		return false;
	}

	//todo try to unify this
	worldSpace.MoveObject(obj, direction);
	obj->CALLED_BY_SIM_Move(direction);
	return true;
}

void Simulation::RemoveObject(GameObject* obj)
{
	worldSpace.RemoveObject(obj);
	entities.remove(obj);
	simulationPrinter->ClearObject(obj);
	delete(obj);
}

void Simulation::LoadLevel (Level* level)
{
	this->level = level;

	for (ISimulationUpdatingEntity* obj : entities)
		delete(obj);

	entities.clear();
	worldSpace.Init(level->GetWorldSizeX(), level->GetWorldSizeY(), GetScreenPadding());
	ResetScreenManager(level->GetBackgroundFileName());
	level->LoadInSimulation();
}

void Simulation::ResetScreenManager(const string& backgroundFileName)
{
	if (simulationPrinter != nullptr)
		delete(simulationPrinter);
	simulationPrinter = new SimulationPrinter(GetScreenSizeX(), GetScreenSizeY(), GetScreenPadding(), backgroundFileName);
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