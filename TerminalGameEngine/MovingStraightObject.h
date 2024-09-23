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
protected:
	Direction moveDirection;

private:
	const float moveSpeed;

	//---------------------------------------------------------- Methods
public:
	MovingStraightObject(int xPos, int yPos, Direction moveDir, float moveSpeed);

protected:
	void Update() override;

};