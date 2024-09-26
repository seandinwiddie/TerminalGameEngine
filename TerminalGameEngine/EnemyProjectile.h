#pragma once
#include "Projectile.h"

class EnemyProjectile : public Projectile
{
//---------------------------------------------------------- Fields
private:
	static const Model MODEL;

//---------------------------------------------------------- Methodss
public:
	using Projectile::Projectile;

protected:
	virtual int GetColor() const { return Terminal::RED; }
	virtual void InitModel() { SetModel(MODEL); }
};

const Model EnemyProjectile::MODEL = { {'|'} };