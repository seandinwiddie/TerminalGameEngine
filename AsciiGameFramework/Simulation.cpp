#include "Simulation.h"

#include "CollidingObject.h"
#include "ScreenManager.h"
#include "SimulationObject.h"
#include "TransformObject.h"
#include "Level.h"
#include "TimeUtils.h"

#include <Windows.h>
#include <cassert>

void Simulation::Step()
{
	if (level->IsTerminated())
		return;
		
	level->Update();

	//update all objects
	for (auto it = simulationObjects.rbegin(); it != simulationObjects.rend(); ++it)
		(*it)->Update();

	//detect end of collisions
	for (auto it = simulationObjects.rbegin(); it != simulationObjects.rend(); ++it)
	{
		CollidingObject* collidingObj = dynamic_cast<CollidingObject*>((*it));
		if (collidingObj != nullptr)
			UpdateObjectCollisionDirections(collidingObj);
	}

	// print frame
	if (++printFrameStep == STEPS_PER_FRAME)
	{
		for (SimulationObject* obj : simulationObjects)
		{
			TransformObject* transformObj = dynamic_cast<TransformObject*>(obj);
			if(transformObj != nullptr)
				screenManager->InsertGameObject(transformObj);
		}
			

		screenManager->PrintFrameOnTerminal();
		screenManager->ClearFrame();
		printFrameStep = 0;

		TimeUtils::Instance().NotifyFrameGenerated();

		double deltaTimeMilliseconds = TimeUtils::Instance().GetDeltaTime() * 1000;
		if(deltaTimeMilliseconds < PREVENT_SCEEN_REFRESH_BEFORE_MILLISECONDS)
			Sleep(PREVENT_SCEEN_REFRESH_BEFORE_MILLISECONDS - deltaTimeMilliseconds);
	}
}

void Simulation::UpdateObjectCollisionDirections(CollidingObject* obj)
{
	std::vector<bool> collidingDirections(4);

	unsigned int x = obj->GetPosX();
	unsigned int y = obj->GetPosY();
	unsigned int xMax = obj->GetMaxPosX();
	unsigned int yMax = obj->GetMaxPosY();
	unsigned int width = obj->GetModelWidth();
	unsigned int height = obj->GetModelHeight();
	bool canExitScreen = obj->CanExitScreenSpace();

	// object - screen margin collisions
	bool isCollidingWithScreenUp = !canExitScreen && !IsCoordinateInsideScreenSpace(x, yMax + 1);
	bool isCollidingWithScreenDown = !canExitScreen && !IsCoordinateInsideScreenSpace(x, y - 1);
	bool isCollidingWithScreenRight = !canExitScreen && !IsCoordinateInsideScreenSpace(xMax + 1, y);
	bool isCollidingWithScreenLeft = !canExitScreen && !IsCoordinateInsideScreenSpace(x - 1, y);

	// object-object collisions
	
	// Using collision COLLISION_END_DISTANCE = 2 prevents detecting repeated collisions if a faster object is pushing 
	// a slower one. In the future the collision detection system could be improved in order to move faster 
	// objects after slower ones during the same frame, doing this collision depth could be set to 1. (todo)
	const int COLLISION_END_DISTANCE_X = 2;
	const int COLLISION_END_DISTANCE_Y = 1;
	collidingDirections[static_cast<int>(Direction::up)] =
		(!IsSpaceEmpty(x, yMax + 1, width, COLLISION_END_DISTANCE_Y) || isCollidingWithScreenUp);

	collidingDirections[static_cast<int>(Direction::down)] =
		(!IsSpaceEmpty(x, y - COLLISION_END_DISTANCE_Y, width, COLLISION_END_DISTANCE_Y) || isCollidingWithScreenDown);

	collidingDirections[static_cast<int>(Direction::left)] =
		(!IsSpaceEmpty(x - COLLISION_END_DISTANCE_X, y, COLLISION_END_DISTANCE_X, height) || isCollidingWithScreenRight);

	collidingDirections[static_cast<int>(Direction::right)] =
		(!IsSpaceEmpty(xMax + 1, y, COLLISION_END_DISTANCE_X, height) || isCollidingWithScreenLeft);

	obj->UpdateCollidingDirecitons(collidingDirections);
} 

bool Simulation::IsSpaceEmpty(const int startingX, const int startingY, const int width, const int height) const
{
	for (int y = startingY; y < startingY + height; ++y)
		for (int x = startingX; x < startingX + width; ++x)
			if (IsCoordinateInsideGameSpace(x, y) && gameSpace[y][x] != nullptr)
				return false;

	return true;
}

bool Simulation::TryAddGameObject(TransformObject* obj)
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

	simulationObjects.push_back(obj);

	return true;
}

bool Simulation::CanObjectBeAdded(const TransformObject* const obj) const
{
	if (IsInSimulation(obj))
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

bool Simulation::IsInSimulation(const TransformObject* obj) const
{
	for (SimulationObject* simulationObj : simulationObjects)
		if (obj == simulationObj)
			return true;

	return false;
}

bool Simulation::TryMoveAtDirection(TransformObject* obj, const Direction direction)
{
	assert(IsInSimulation(obj));

	CollidingObject* collidingObj = dynamic_cast<CollidingObject*>(obj);
	CollidingObject* outOtherObj;
	if (CanMoveAtDirection(obj, direction, outOtherObj) == false)
	{
		// colliding with none -> exiting world
		if (outOtherObj == nullptr)
		{
			if(obj->CanExitScreenSpace())
				RemoveGameObject(obj);
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
			++obj->yPos;
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
			--obj->yPos;
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
			++obj->xPos;
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
				--obj->xPos;
			}
			break;
		}

		return true;
	}
}

bool Simulation::CanMoveAtDirection
(
	const TransformObject* obj,
	Direction direction, 
	CollidingObject*& outCollidingObject
) const
{
	assert(IsInSimulation(obj));

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

void Simulation::RemoveGameObject(TransformObject* obj)
{
	assert(IsInSimulation(obj));

	for(int y = obj-> GetPosY(); y <= obj->GetMaxPosY(); ++y)
		for (int x = obj->GetPosX(); x <= obj->GetMaxPosX(); ++x)
		{
			assert(gameSpace[y][x] == obj);
			gameSpace[y][x] = nullptr;
		}
			
	simulationObjects.remove(obj);
	delete(obj);
}

void Simulation::Reset
(
Level* level,
const unsigned int worldSizeX, 
const unsigned int worldSizeY,
const unsigned int screenPadding,
const bool showLevelTime,
const const std::vector<string>& backgroundFileNames
)
{
	this->level = level;
	this->worldSizeX = worldSizeX;
	this->worldSizeY = worldSizeY;
	this->screenPadding = screenPadding;
	//isGameStarting = true;

	ResetScreenManager(showLevelTime, backgroundFileNames);
	
	//clear simulation variables
	for (SimulationObject* obj : simulationObjects)
		delete(obj);
	simulationObjects.clear();

	// clear gamespace
	gameSpace.clear();
	gameSpace.resize(worldSizeY);

	for (int y = 0; y < worldSizeY; ++y)
	{
		gameSpace[y].resize(worldSizeX);
		for (auto elem : gameSpace[y])
			elem = nullptr;
	}

	printFrameStep = 0;
	levelStartedTime = TimeUtils::Instance().GetTime();
}

void Simulation::ResetScreenManager(bool showLevelTime, const std::vector<string>& backgroundFileNames)
{
	if (screenManager != nullptr)
		delete(screenManager);
	screenManager = new ScreenManager(worldSizeX, worldSizeY, screenPadding, showLevelTime, backgroundFileNames);
}

bool Simulation::IsCoordinateInsideGameSpace(const int x, const int y) const
{ 
	return
		y >= 0 && y < worldSizeY &&
		x >= 0 && x < worldSizeX;
}

bool Simulation::IsCoordinateInsideScreenSpace(const int x, const int y) const
{
	return
		y >= screenPadding &&
		y < worldSizeY - screenPadding &&
		x >= screenPadding &&
		x < worldSizeX - screenPadding;
}