#pragma once
#include "Projectile.h"

class PlayerProjectile : public Projectile
{
//---------------------------------------------------------- Fields
private:
	static const Model MODEL;

//---------------------------------------------------------- Methodss
public:
	//todo use this in other classes where needed
	using Projectile::Projectile;

protected:
	virtual int GetColor() const { return Terminal::GREEN; }
	virtual void InitModel() { SetModel(MODEL); }
	virtual void OnCollisionEnter(GameObject* other, Direction collisionDir);
};