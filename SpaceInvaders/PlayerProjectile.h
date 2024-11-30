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
		virtual int GetColor() const { return Engine::Terminal::GREEN; }
		virtual void InitModel() { SetModel(MODEL); }
		virtual void OnCollisionEnter(shared_ptr<Collider> other, Direction collisionDir);
	};
}