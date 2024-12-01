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
		bool CanExitScreenSpace() const override { assert(false); return true; }
		double GetGravityScale() const override { assert(false); return 0; }
		void InitModel() override {}
	};
}