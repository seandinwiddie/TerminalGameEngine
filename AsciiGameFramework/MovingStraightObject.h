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

	MovingStraightObject(int xPos, int yPos, Direction moveDir, float moveSpeed);
	void Update() override;

};