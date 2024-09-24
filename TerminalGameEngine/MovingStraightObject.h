#pragma once

#include "GameObject.h"

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <cassert>

class MovingStraightObject : public GameObject
{
//---------------------------------------------------------- Fields
private:
	Direction moveDirection;
	const double moveSpeed;

//---------------------------------------------------------- Methods
public:
	MovingStraightObject(int xPos, int yPos, Direction moveDir, double moveSpeed);

protected:
	void Update() override;
};