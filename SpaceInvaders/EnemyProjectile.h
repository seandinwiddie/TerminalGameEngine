#pragma once
#include "Projectile.h"
#include "GameObject.h"

namespace SpaceInvaders
{
	class EnemyProjectile : public Projectile
	{
		//---------------------------------------------------------- Fields
	private:
		static const Engine::Model MODEL;

		//---------------------------------------------------------- Methodss
	public:
		using Projectile::Projectile;

	protected:
		virtual int GetColor() const { return Engine::Terminal::RED; }
		virtual void InitModel() { SetModel(MODEL); }
		virtual void OnCollisionEnter(Collider* other, Direction collisionDir);
	};
}