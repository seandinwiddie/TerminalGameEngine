#include "Projectile.h"
#include "ShieldPart.h"
#include "Simulation.h"

void Projectile::OnCollisionEnter(GameObject* other, Direction collisionDir)
{
	MovingStraightObject::OnCollisionEnter(other, collisionDir);
	ShieldPart* otherShieldPart = dynamic_cast<ShieldPart*>(other);
	if (otherShieldPart != nullptr)
		Simulation::Instance().RemoveEntity(otherShieldPart);
}