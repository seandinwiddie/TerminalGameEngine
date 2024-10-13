#pragma once

#include "Collider.h"
#include <cassert>

namespace Engine
{
	class FakeCollider : public Collider
	{
	public:
		FakeCollider() : Collider(0, 0) {}
	private:
		virtual bool CanExitScreenSpace() const override { assert(false); return true; }
		virtual double GetGravityScale() const override { assert(false); return 0; }
		virtual void InitModel() override {}
	};
}