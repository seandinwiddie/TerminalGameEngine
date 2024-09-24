#pragma once
#include "GameObject.h"
#include <cassert>

class FakeGameObject : public GameObject
{
public:
	FakeGameObject() :GameObject(0, 0) {}
private:
	virtual void OnCollisionEnter(GameObject* other, Direction collisionDir) override { assert(false); }
	virtual void OnCollisionExit(Direction endingCollisionDir) override { assert(false); }
	virtual bool CanExitScreenSpace() const override { assert(false); return true; }
	virtual double GetGravityScale() const override { assert(false); return 0; }
	virtual void InitModel() override {}
};