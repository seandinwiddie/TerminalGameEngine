#include "Simulation.h"

#include "GameObject.h"
#include "SimulationPrinter.h"
#include "ISimulationUpdatingEntity.h"
#include "GameObject.h"
#include "Level.h"
#include "TimeHelper.h"

#include <Windows.h>
#include <cassert>


void Simulation::RequestMovement(GameObject* applicantObj, Direction direction, float speed)
{
	MoveRequest request(applicantObj, direction, speed);

	auto it = moveRequests.begin();
	for (; it != moveRequests.end(); ++it)
		if (it->speed > request.speed)
			break;

	moveRequests.insert(it, request);
}

void Simulation::Step()
{
	if (level->IsTerminated())
		return;

	moveRequests.clear();

	//---------------- update all objects
	for (ISimulationUpdatingEntity* updatable : entities)
		updatable->Update();
	level->Update();

	//---------------- move objects (slower ones first)
	for (auto it = moveRequests.begin(); it != moveRequests.end(); ++it)
	{
		int oldXPos = it->object->GetPosX();
		int oldYPos = it->object->GetPosY();

		if (TryMoveObjectAtDirection(it->object, it->direction))
		{
			simulationPrinter->Clear(oldXPos, oldYPos, it->object->GetModelWidth(), it->object->GetModelHeight());
			it->object->mustBeReprinted = true;
		}
	}

	//---------------- detect end of collisions
	for (auto it = entities.rbegin(); it != entities.rend(); ++it)
	{
		GameObject* obj = dynamic_cast<GameObject*>((*it));
		if (obj != nullptr)
			UpdateObjectCollisionDirections(obj);
	}

	//---------------- 
	for (ISimulationUpdatingEntity* updatingEntity : entities)
	{
		GameObject* obj = dynamic_cast<GameObject*>(updatingEntity);
		if (obj != nullptr && obj->mustBeReprinted)
		{
			obj->mustBeReprinted = false;
			simulationPrinter->PrintObject(obj);
		}
	}

	//----------------
	TimeHelper::Instance().NotifyFrameGenerated();
	lastTimePrintedFrame = TimeHelper::Instance().GetTime();

#if DEBUG_MODE && SHOW_FPS
	simulationPrinter->DEBUG_PrintAverageFps();
#endif
}

void Simulation::UpdateObjectCollisionDirections(GameObject* obj)
{
	std::vector<bool> collidingDirections(4);

	int x = obj->GetPosX();
	int y = obj->GetPosY();
	int xMax = obj->GetMaxPosX();
	int yMax = obj->GetMaxPosY();
	uint width = obj->GetModelWidth();
	uint height = obj->GetModelHeight();
	bool canExitScreen = obj->CanExitScreenSpace();

	// object - screen margin collisions
	bool isCollidingWithScreenUp = !canExitScreen && !IsCoordinateInsideScreenSpace(x, yMax + 1);
	bool isCollidingWithScreenDown = !canExitScreen && !IsCoordinateInsideScreenSpace(x, y - 1);
	bool isCollidingWithScreenRight = !canExitScreen && !IsCoordinateInsideScreenSpace(xMax + 1, y);
	bool isCollidingWithScreenLeft = !canExitScreen && !IsCoordinateInsideScreenSpace(x - 1, y);

	// object-object collisions
	collidingDirections[static_cast<int>(Direction::up)] =
		(!IsSpaceEmpty(x, yMax + 1, width, 1) || isCollidingWithScreenUp);

	collidingDirections[static_cast<int>(Direction::down)] =
		(!IsSpaceEmpty(x, y - 1, width, 1) || isCollidingWithScreenDown);

	collidingDirections[static_cast<int>(Direction::left)] =
		(!IsSpaceEmpty(x - 1, y, 1, height) || isCollidingWithScreenLeft);

	collidingDirections[static_cast<int>(Direction::right)] =
		(!IsSpaceEmpty(xMax + 1, y, 1, height) || isCollidingWithScreenRight);

	obj->CALLED_BY_SIM_UpdateCollidingDirecitons(collidingDirections);
} 

bool Simulation::IsSpaceEmpty(uint startingX, uint startingY, uint width, uint height) const
{
	for (int y = startingY; y < startingY + height; ++y)
		for (int x = startingX; x < startingX + width; ++x)
			if (IsCoordinateInsideGameSpace(x, y) && worldSpace[y][x] != nullptr)
				return false;

	return true;
}

bool Simulation::TryAddEntity(ISimulationUpdatingEntity* updatingEntity)
{
	GameObject* gameObjectEntity = dynamic_cast<GameObject*>(updatingEntity);

	if (gameObjectEntity != nullptr)
	{
		if (!CanObjectBeAdded(gameObjectEntity))
		{
			delete(updatingEntity);
			return false;
		}

		gameObjectEntity->mustBeReprinted = false;
		simulationPrinter->PrintObject(gameObjectEntity);
	}

	GameObject* obj = dynamic_cast<GameObject*>(updatingEntity);
	if (obj != nullptr)
	{
		// Colliding object model must be setup before adding it to simulation
		assert(obj->GetModel().size() > 0);

		for (int y = obj->GetPosY(); y <= obj->GetMaxPosY(); ++y)
			for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); ++x)
				worldSpace[y][x] = obj;
	}

	entities.push_back(updatingEntity);
	
	return true;
}

bool Simulation::CanObjectBeAdded(const GameObject* obj) const
{
	if (IsObjectInSimulation(obj))
		return false;

	for (int y = obj->GetPosY(); y <= obj->GetMaxPosY(); ++y)
		for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); ++x)
		{
			if (IsCoordinateInsideGameSpace(x, y) == false)
				return false;

			if (worldSpace[y][x] != nullptr)
				return false;
		}
			
	return true;
}

bool Simulation::IsObjectInSimulation(const ISimulationUpdatingEntity* obj) const
{
	for (ISimulationUpdatingEntity* simulationObj : entities)
		if (obj == simulationObj)
			return true;

	return false;
}

bool Simulation::TryMoveObjectAtDirection(GameObject* obj, Direction direction)
{
	assert(IsObjectInSimulation(obj));
	GameObject* outOtherObj;

	if (CanObjectMoveAtDirection(obj, direction, outOtherObj) == false)
	{
		// colliding with none -> exiting world / colliding with screen margin
		if (outOtherObj == nullptr)
		{
			if (obj->CanExitScreenSpace())
			{
				RemoveObject(obj);
			}
			else
			{
				//notify collision with screen margin
				obj->CALLED_BY_SIM_NotifyCollision(nullptr, direction);
			}
				
		}
		else
		{
			obj->CALLED_BY_SIM_NotifyCollision(outOtherObj, direction);
			outOtherObj->CALLED_BY_SIM_NotifyCollision(obj, GetInverseDirection(direction));
		}

		return false;
	}

	switch (direction)
	{
		case Direction::up:
		{
			int yWrite = obj->GetMaxPosY() + 1;
			int yClear = obj->GetPosY();
			for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); ++x)
			{
				worldSpace[yWrite][x] = obj;
				worldSpace[yClear][x] = nullptr;
			}
			MoveObject(obj, direction);
			break;
		}
		case Direction::down:
		{
			int yWrite = obj->GetPosY() - 1;
			int yClear = obj->GetMaxPosY();
			for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); ++x)
			{
				worldSpace[yWrite][x] = obj;
				worldSpace[yClear][x] = nullptr;
			}
			MoveObject(obj, direction);
			break;
		}
		case Direction::right:
		{
			int xWrite = obj->GetMaxPosX() + 1;
			int xClear = obj->GetPosX();
			for (int y = obj->GetPosY(); y <= obj->GetMaxPosY(); ++y)
			{
				worldSpace[y][xWrite] = obj;
				worldSpace[y][xClear] = nullptr;
			}
			MoveObject(obj, direction);
			break;
		}

		case Direction::left:
		{
			int xWrite = obj->GetPosX() - 1;
			int xClear = obj->GetMaxPosX();
			for (int y = obj->GetPosY(); y <= obj->GetMaxPosY(); ++y)
			{
				worldSpace[y][xWrite] = obj;
				worldSpace[y][xClear] = nullptr;
			}
			MoveObject(obj, direction);
			break;
		}

		return true;
	}
}

bool Simulation::CanObjectMoveAtDirection
(
	const GameObject* obj,
	Direction direction, 
	GameObject*& outCollidingObject
) const
{
	assert(IsObjectInSimulation(obj));

	switch (direction)
	{
		case Direction::up:
		{
			int y = obj->GetMaxPosY() + 1;

			//exiting world
			if (y == GetWorldSizeY())
			{
				//colliding with nullptr = exiting world
				outCollidingObject = nullptr;
				return false;
			}
			
			//exiting screen space
			if (obj->CanExitScreenSpace() == false)
			{
				if (y == GetWorldSizeY() - GetScreenPadding())
				{
					//colliding with nullptr = exiting screen space
					outCollidingObject = nullptr;
					return false;
				}
			}

			//check collision
			for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); x++)
			{
				if (worldSpace[y][x] != nullptr)
				{
					outCollidingObject = worldSpace[y][x];
					return false;
				}
			}

			return true;
		}
		case Direction::down:
		{
			int y = obj->GetPosY() - 1;

			if (y == -1)
			{
				outCollidingObject = nullptr;
				return false;
			}

			//exiting screen space
			if (obj->CanExitScreenSpace() == false)
			{
				if (y == GetScreenPadding() - 1)
				{
					//colliding with nullptr = exiting screen space
					outCollidingObject = nullptr;
					return false;
				}
			}

			//check collision
			for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); x++)
			{
				if (worldSpace[y][x] != nullptr)
				{
					outCollidingObject = worldSpace[y][x];
					return false;
				}
			}
			
			return true;
		}
		case Direction::right:
		{
			int x = obj->GetMaxPosX() + 1;

			if (x == GetWorldSizeX())
			{
				outCollidingObject = nullptr;
				return false;
			}

			//exiting screen space
			if (obj->CanExitScreenSpace() == false)
			{
				if (x == GetWorldSizeX() - GetScreenPadding())
				{
					//colliding with nullptr = exiting screen space
					outCollidingObject = nullptr;
					return false;
				}
			}

			//check collision
			for (int y = obj->GetPosY(); y <= obj->GetMaxPosY(); y++)
			{
				if (worldSpace[y][x] != nullptr)
				{
					outCollidingObject = worldSpace[y][x];
					return false;
				}
			}
			
			return true;
		}
		case Direction::left:
		{
			int x = obj->GetPosX() - 1;

			if (x == -1)
			{
				outCollidingObject = nullptr;
				return false;
			}
			
			//exiting screen space
			if (obj->CanExitScreenSpace() == false)
			{
				if (x == GetScreenPadding() - 1)
				{
					//colliding with nullptr = exiting screen space
					outCollidingObject = nullptr;
					return false;
				}
			}

			//check collision
			for (int y = obj->GetPosY(); y <= obj->GetMaxPosY(); y++)
			{
				if (worldSpace[y][x] != nullptr)
				{
					outCollidingObject = worldSpace[y][x];
					return false;
				}
			}
			
			return true;
		}
	}
}

void Simulation::RemoveObject(GameObject* obj)
{
	assert(IsObjectInSimulation(obj));

	for(int y = obj-> GetPosY(); y <= obj->GetMaxPosY(); ++y)
		for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); ++x)
		{
			assert(worldSpace[y][x] == obj);
			worldSpace[y][x] = nullptr;
		}
	entities.remove(obj);
	simulationPrinter->Clear(obj);
	delete(obj);
}

void Simulation::LoadLevel (Level* level)
{
	this->level = level;
	
	//clear simulation variables
	for (ISimulationUpdatingEntity* obj : entities)
		delete(obj);
	entities.clear();

	// clear gamespace
	worldSpace.clear();
	worldSpace.resize(level->GetWorldSizeY());

	ResetScreenManager(level->GetBackgroundFileName());

	for (int y = 0; y < level->GetWorldSizeY(); ++y)
	{
		worldSpace[y].resize(level->GetWorldSizeX());
		for (auto elem : worldSpace[y])
			elem = nullptr;
	}

	levelStartedTime = TimeHelper::Instance().GetTime();

	level->LoadInSimulation();
}

void Simulation::MoveObject(GameObject* obj, Direction direction)
{
	switch (direction)
	{
	case Direction::up:
		++obj->yPos;
		obj->yPosContinuous = obj->yPos;
		break;
	case Direction::down:
		--obj->yPos;
		obj->yPosContinuous = obj->yPos;
		break;
	case Direction::right:
		++obj->xPos;
		obj->xPosContinuous = obj->xPos;
		break;
	case Direction::left:
		--obj->xPos;
		obj->xPosContinuous = obj->xPos;
		break;
	}
}

void Simulation::ResetScreenManager(const string& backgroundFileName)
{
	if (simulationPrinter != nullptr)
		delete(simulationPrinter);
	simulationPrinter = new SimulationPrinter(GetScreenSizeX(), GetScreenSizeY(), GetScreenPadding(), backgroundFileName);
}

bool Simulation::IsInsideGameSpaceX(int xPos) const
{
	return xPos >= 0 && xPos < GetWorldSizeX();
}

bool Simulation::IsInsideGameSpaceY(int yPos) const
{
	return yPos >= 0 && yPos < GetWorldSizeY();
}

bool Simulation::IsCoordinateInsideGameSpace(int xPos, int yPos) const
{ 
	return IsInsideGameSpaceX(xPos) && IsInsideGameSpaceY(yPos);
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

bool Simulation::IsCoordinateInsideScreenSpace(int xPos, int yPos) const
{
	auto test = IsInsideScreenX(xPos);
	auto test2 = IsInsideScreenY(yPos);
	return IsInsideScreenX(xPos) && IsInsideScreenY(yPos);
}

void Simulation::PrintUIFrame(const Frame& UIMessage) { simulationPrinter->PrintUIFrame(UIMessage); }

void  Simulation::SetTerminalHeader(const string& header) { simulationPrinter->SetHeader(header); }