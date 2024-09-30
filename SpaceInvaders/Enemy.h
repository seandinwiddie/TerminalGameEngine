#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
//------------------------------------------------------ Fields
public:
	using GameObject::GameObject;
protected:
	bool isFirsAnimationFrameTime;

//------------------------------------------------------ Methods
public:
	virtual size_t GetScore() const = 0;

protected:
	virtual double GetGravityScale() const override { return 0; }
	virtual void StepAnimation() = 0;
	virtual void Update() override;
};