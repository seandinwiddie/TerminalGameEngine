#pragma once
#include "Projectile.h"

namespace SpaceInvaders
{
	using Model = Engine::Model;

	class PlayerProjectile : public Projectile
	{
		//---------------------------------------------------------- Fields
	private:
		static const Model MODEL;

		//---------------------------------------------------------- Methodss
	public:
		using Projectile::Projectile;

	protected:
		int GetColor() const override { return Engine::Terminal::GREEN; }
		void InitModel() override { SetModel(MODEL); }
		void OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir) override;
	};
}