#pragma once
#include "Collider.h"

class Enemy : public Collider
{
//------------------------------------------------------ Fields
public:
	using Collider::Collider;
protected:
	bool isFirsAnimationFrameTime;

//------------------------------------------------------ Methods
public:
	virtual size_t GetScore() const = 0;

protected:
	virtual double GetGravityScale() const override { return 0; }
	virtual void OnDestroy() override;
};