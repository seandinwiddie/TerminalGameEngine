#pragma once
#include "Enemy.h"
#include "Terminal.h"
#include "DirectionUtils.h"
#include <array>

namespace SpaceInvaders
{
	using Direction = Engine::Direction;
	using Model = Engine::Model;

	class Ufo : public Enemy
	{
		//------------------------------------------------------ Fields
	private:
		static const Model MODEL_1;
		static const std::array<size_t, 6> POSSIBLE_SCORES;
		static const size_t MOVE_SPEED = 8;

		Direction moveDirection;
		//------------------------------------------------------ Methods
	public:
		Ufo(int xPos, int yPos, Direction moveDirection) : Enemy(xPos, yPos), moveDirection(moveDirection) {};

		virtual bool CanExitScreenSpace() const override { return true; }
		virtual int GetColor() const override { return Engine::Terminal::RED; }
		virtual void InitModel() { SetModel(MODEL_1); }
		virtual size_t GetScore() const;

	protected:
		virtual void Update() override;
		virtual void OnCollisionEnter(Collider* other, Direction collisionDir) override;
		virtual int GetDestroyedParticlesColor() { return Engine::Terminal::RED; }
	};
}