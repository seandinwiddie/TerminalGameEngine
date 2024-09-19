#include "Simulation.h"

#include "CollidingObject.h"
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

	for (ISimulationUpdatingEntity* updatable : updatingEntities)
		updatable->Update();

	level->Update();
	for (auto it = objects.rbegin(); it != objects.rend(); ++it)
		(*it)->Update();

	//---------------- move objects (slower ones first)
	for (auto it = moveRequests.begin(); it != moveRequests.end(); ++it)
		TryMoveObjectAtDirection(it->object, it->direction);


	//---------------- detect end of collisions
	for (auto it = objects.rbegin(); it != objects.rend(); ++it)
	{
		CollidingObject* collidingObj = dynamic_cast<CollidingObject*>((*it));
		if (collidingObj != nullptr)
			UpdateObjectCollisionDirections(collidingObj);
	}

	//---------------- print frame
	if (++printFrameStep == STEPS_PER_FRAME)
	{
		for (ISimulationUpdatingEntity* simUpdatable : objects)
		{
			GameObject* obj = dynamic_cast<GameObject*>(simUpdatable);
			if(obj != nullptr)
				simulationPrinter->PrintObjectOnFrame(obj);
		}
			

		simulationPrinter->ShowFrameInTerminal();
		simulationPrinter->ClearFrame();
		printFrameStep = 0;

		TimeHelper::Instance().NotifyFrameGenerated();
	}
}

void Simulation::UpdateObjectCollisionDirections(CollidingObject* obj)
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
		(!IsSpaceEmpty(x - 1, y, 1, height) || isCollidingWithScreenRight);

	collidingDirections[static_cast<int>(Direction::right)] =
		(!IsSpaceEmpty(xMax + 1, y, 1, height) || isCollidingWithScreenLeft);

	obj->UpdateCollidingDirecitons(collidingDirections);
} 

bool Simulation::IsSpaceEmpty(uint startingX, uint startingY, uint width, uint height) const
{
	for (int y = startingY; y < startingY + height; ++y)
		for (int x = startingX; x < startingX + width; ++x)
			if (IsCoordinateInsideGameSpace(x, y) && gameSpace[y][x] != nullptr)
				return false;

	return true;
}

void Simulation::AddUpdatable(ISimulationUpdatingEntity* updatable)
{
	updatingEntities.push_back(updatable);
}

bool Simulation::TryAddObject(GameObject* obj)
{
	if (CanObjectBeAdded(obj) == false)
		return false;

	CollidingObject* collidingObj = dynamic_cast<CollidingObject*>(obj);
	if (collidingObj != nullptr)
	{
		for (int y = obj->GetPosY(); y <= obj->GetMaxPosY(); ++y)
			for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); ++x)
				gameSpace[y][x] = collidingObj;
	}

	objects.push_back(obj);

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

			if (dynamic_cast<const CollidingObject*>(obj) != nullptr && gameSpace[y][x] != nullptr)
				return false;
		}
			
	return true;
}

bool Simulation::IsObjectInSimulation(const ISimulationUpdatingEntity* obj) const
{
	for (ISimulationUpdatingEntity* simulationObj : objects)
		if (obj == simulationObj)
			return true;

	return false;
}

bool Simulation::TryMoveObjectAtDirection(GameObject* obj, Direction direction)
{
	assert(IsObjectInSimulation(obj));

	CollidingObject* collidingObj = dynamic_cast<CollidingObject*>(obj);
	CollidingObject* outOtherObj;

	if (CanObjectMoveAtDirection(obj, direction, outOtherObj) == false)
	{
		// colliding with none -> exiting world
		if (outOtherObj == nullptr)
		{
			if(obj->CanExitScreenSpace())
				RemoveObject(obj);
			else
				collidingObj->NotifyCollision(nullptr, direction); //notify collision with screen margin
		}
		else
		{
			if (collidingObj != nullptr)
			{
				collidingObj->NotifyCollision(outOtherObj, direction);
				outOtherObj->NotifyCollision(collidingObj, GetInverseDirection(direction));
			}
		}

		return false;
	}

	switch (direction)
	{
		case Direction::up:
		{
			if (collidingObj != nullptr)
			{
				int yWrite = obj->GetMaxPosY() + 1;
				int yClear = obj->GetPosY();
				for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); ++x)
				{
					gameSpace[yWrite][x] = collidingObj;
					gameSpace[yClear][x] = nullptr;
				}
			}
			MoveObject(obj, direction);
			break;
		}
		case Direction::down:
		{
			if (collidingObj != nullptr)
			{
				int yWrite = obj->GetPosY() - 1;
				int yClear = obj->GetMaxPosY();
				for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); ++x)
				{
					gameSpace[yWrite][x] = collidingObj;
					gameSpace[yClear][x] = nullptr;
				}
			}
			MoveObject(obj, direction);
			break;
		}
		case Direction::right:
		{
			if (collidingObj != nullptr)
			{
				int xWrite = obj->GetMaxPosX() + 1;
				int xClear = obj->GetPosX();
				for (int y = obj->GetPosY(); y <= obj->GetMaxPosY(); ++y)
				{
					gameSpace[y][xWrite] = collidingObj;
					gameSpace[y][xClear] = nullptr;
				}
			}
			MoveObject(obj, direction);
			break;
		}

		case Direction::left:
		{
			if (collidingObj != nullptr)
			{
				int xWrite = obj->GetPosX() - 1;
				int xClear = obj->GetMaxPosX();
				for (int y = obj->GetPosY(); y <= obj->GetMaxPosY(); ++y)
				{
					gameSpace[y][xWrite] = collidingObj;
					gameSpace[y][xClear] = nullptr;
				}
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
	CollidingObject*& outCollidingObject
) const
{
	assert(IsObjectInSimulation(obj));

	switch (direction)
	{
		case Direction::up:
		{
			int y = obj->GetMaxPosY() + 1;

			//exiting world
			if (y == worldSizeY)
			{
				//colliding with nullptr = exiting world
				outCollidingObject = nullptr;
				return false;
			}
			
			//exiting screen space
			if (obj->CanExitScreenSpace() == false)
			{
				if (y == worldSizeY - screenPadding)
				{
					//colliding with nullptr = exiting screen space
					outCollidingObject = nullptr;
					return false;
				}
			}

			//colliding
			if (dynamic_cast<const CollidingObject*>(obj) != nullptr)
			{
				for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); x++)
				{
					if (gameSpace[y][x] != nullptr)
					{
						outCollidingObject = gameSpace[y][x];
						return false;
					}

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
				if (y == screenPadding-1)
				{
					//colliding with nullptr = exiting screen space
					outCollidingObject = nullptr;
					return false;
				}
			}

			if (dynamic_cast<const CollidingObject*>(obj) != nullptr)
			{
				for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); x++)
				{
					if (gameSpace[y][x] != nullptr)
					{
						outCollidingObject = gameSpace[y][x];
						return false;
					}
				}
			}
			
			return true;
		}
		case Direction::right:
		{
			int x = obj->GetMaxPosX() + 1;

			if (x == worldSizeX)
			{
				outCollidingObject = nullptr;
				return false;
			}

			//exiting screen space
			if (obj->CanExitScreenSpace() == false)
			{
				if (x == worldSizeX - screenPadding)
				{
					//colliding with nullptr = exiting screen space
					outCollidingObject = nullptr;
					return false;
				}
			}

			if (dynamic_cast<const CollidingObject*>(obj) != nullptr)
			{
				for (int y = obj->GetPosY(); y <= obj->GetMaxPosY(); y++)
				{
					if (gameSpace[y][x] != nullptr)
					{
						outCollidingObject = gameSpace[y][x];
						return false;
					}
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
				if (x == screenPadding-1)
				{
					//colliding with nullptr = exiting screen space
					outCollidingObject = nullptr;
					return false;
				}
			}

			if (dynamic_cast<const CollidingObject*>(obj) != nullptr)
			{
				for (int y = obj->GetPosY(); y <= obj->GetMaxPosY(); y++)
				{
					if (gameSpace[y][x] != nullptr)
					{
						outCollidingObject = gameSpace[y][x];
						return false;
					}
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
			assert(gameSpace[y][x] == obj);
			gameSpace[y][x] = nullptr;
		}
			
	objects.remove(obj);
	delete(obj);
}

void Simulation::Reset
(
Level* level,
uint worldSizeX, 
uint worldSizeY,
uint screenPadding,
bool showLevelTime,
const std::vector<string>& backgroundFileNames
)
{
	this->level = level;
	this->worldSizeX = worldSizeX;
	this->worldSizeY = worldSizeY;
	this->screenPadding = screenPadding;
	//isGameStarting = true;

	ResetScreenManager(showLevelTime, backgroundFileNames);
	
	//clear simulation variables
	for (ISimulationUpdatingEntity* obj : objects)
		delete(obj);
	objects.clear();

	// clear gamespace
	gameSpace.clear();
	gameSpace.resize(worldSizeY);

	for (int y = 0; y < worldSizeY; ++y)
	{
		gameSpace[y].resize(worldSizeX);
		for (auto elem : gameSpace[y])
			elem = nullptr;
	}

	for (ISimulationUpdatingEntity* updatingEntity : updatingEntities)
		delete(updatingEntity);
	updatingEntities.clear();

	printFrameStep = 0;
	levelStartedTime = TimeHelper::Instance().GetTime();
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

void Simulation::ResetScreenManager(bool showLevelTime, const std::vector<string>& backgroundFileNames)
{
	if (simulationPrinter != nullptr)
		delete(simulationPrinter);
	simulationPrinter = new SimulationPrinter(GetScreenSizeX(), GetScreenSizeY(), screenPadding, showLevelTime, backgroundFileNames);
}

bool Simulation::IsInsideGameSpaceX(int xPos) const
{
	return xPos >= 0 && xPos < worldSizeX;
}

bool Simulation::IsInsideGameSpaceY(int yPos) const
{
	return yPos >= 0 && yPos < worldSizeY;
}

bool Simulation::IsCoordinateInsideGameSpace(int xPos, int yPos) const
{ 
	return IsInsideGameSpaceX(xPos) && IsInsideGameSpaceY(yPos);
}

bool Simulation::IsInsideScreenY(int yPos) const
{
	return
		yPos >= screenPadding &&
		yPos < worldSizeY - screenPadding;
}
bool Simulation::IsInsideScreenX(int xPos) const
{
	return 
		xPos >= screenPadding &&
		xPos < worldSizeX - screenPadding;
}

bool Simulation::IsCoordinateInsideScreenSpace(int xPos, int yPos) const
{
	return IsInsideScreenX(xPos) && IsInsideScreenY(yPos);
}

void Simulation::ShowUIFrame(const Frame& UIMessage) { simulationPrinter->ShowUIFrame(UIMessage); }