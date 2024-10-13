#pragma once
#include "ISimulationEntity.h"
#include "GridDirection.h"
#include "AliensFrontline.h"
#include "Event.h"
#include "Vector2D.h"

namespace Engine
{
	class GameObject;
}

namespace SpaceInvaders
{
	using Direction = Engine::Direction;
	
	class Alien;
	class SpaceInvadersLevel;
	using GameObject = Engine::GameObject;

	class AliensController : public Engine::ISimulationEntity
	{
		//------------------------------------------------------------------- Aliens Settings
		//movement
		double const BASE_MOVE_SPEED = 0.5;
		const double ALL_ALIENS_ELIMINATED_MOVE_SPEED_INCREMENT = 16;
		const double WAVE_NUMBER_SPEED_INCREASE_FACTOR = 1;

		//shooting
		const double BASE_SHOOT_DELAY = 1.5;
		const double ALL_ALIENS_ELIMINATED_SHOOT_DELAY_REDUCTION = 0.5;
		const double WAVE_NUMBER_SHOT_DELAY_REDUCTION_FACTOR = 0.1;
		const double SHOTS_RANDOMNESS = 0.5;
		const double MIN_SHOW_DELAY = 0.1;
		//------------------------------------------------------------------- Fields
	public:
		Event<> OnWaveCompleted;
		Event<> OnGroundTouched;

	private:
		SpaceInvadersLevel* level;
		Vector2D<Alien*> aliensGrid;
		AliensFrontline frontLine;

		size_t aliensCount = 0;
		size_t aliensPosX = 0;
		Direction xMoveDirection = Direction::right;
		bool isTimeToMoveAliensDown = false;
		double lastShotTime = -1;
		double shotDelay = 0;
		//------------------------------------------------------------------- Methods
	public:
		AliensController(SpaceInvadersLevel* level) : level(level) {}
		;	void Reset(int aliensCountX, int aliensCountY);
		void Update() override;
		void RegisterAlien(Alien* alien, int xPos, int yPos);

	private:
		double GetSpeedX()const;
		double GetNextShotDelay()const;
		double GetWaveMultiplier()const;
		double GetEliminatedAliensMultiplier()const;
		size_t GetAliensGridHeight() const { return aliensGrid.GetSizeY(); }
		size_t GetAliensGridWidth() const { return aliensGrid.GetSizeX(); }
		size_t GetStartingAliensCount() const { return GetAliensGridWidth() * GetAliensGridHeight(); }
		size_t GetDestroyedAliensCount() const { return GetStartingAliensCount() - aliensCount; }
		void OnAlienMovedCallback(GameObject* alien, Direction moveDirection);
		void OnAlienDestroyedCallback(GameObject* alienObj);
		void OnAliensReachMargin();
		void MoveAliens(Direction dir, double speed);
		void HandleShooting();
		void HandleMovement();
	};
}