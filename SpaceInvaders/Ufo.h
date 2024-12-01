#pragma once
#include "Enemy.h"
#include "Terminal.h"
#include "DirectionUtils.h"
#include <array>

namespace SpaceInvaders
{
	template<typename T> using shared_ptr = std::shared_ptr<T>;
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

		bool CanExitScreenSpace() const override { return true; }
		int GetColor() const override { return Engine::Terminal::RED; }
		void InitModel() override { SetModel(MODEL_1); }
		size_t GetScore() const override;

	protected:
		void Update() override;
		void OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir) override;
		int GetDestroyedParticlesColor() override { return Engine::Terminal::RED; }
	};
}