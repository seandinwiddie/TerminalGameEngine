#pragma once
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <cassert>

#include "CollidingObject.h"

class MovingStraightObject : public CollidingObject
{
	//---------------------------------------------------------- Fields
protected:
	Direction moveDirection;

private:
	const float moveSpeed;

	//---------------------------------------------------------- Methods
public:

	MovingStraightObject(const int xPos, const int yPos, const Direction moveDir, const float moveSpeed);
	void Update() override;

};