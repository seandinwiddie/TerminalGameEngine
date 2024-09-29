#pragma once

#include "GameObject.h"
#include <cassert>

class FakeGameObject : public GameObject
{
public:
	FakeGameObject() : GameObject(0, 0) {}
private:
	virtual bool CanExitScreenSpace() const override { assert(false); return true; }
	virtual double GetGravityScale() const override { assert(false); return 0; }
	virtual void InitModel() override {}
};