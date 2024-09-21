#include "PongLevel.h"
#include "Simulation.h"
#include "PongBar.h"
#include "PongBall.h"

void PongLevel::Load()
{
	Level::Load();
	Simulation& simulation = Simulation::Instance();
	
	int startingPosY = GetWorldSizeY() / 2;
	float barsMoveSpeed = 4;

	PongBar* pongBarLeft = new PongBar(GetScreenPadding()+1, startingPosY, 1, 4, '0', barsMoveSpeed, true);
	simulation.TryAddObject(pongBarLeft);

	PongBar* pongBarRight = new PongBar(GetWorldSizeX() - GetScreenPadding() -1, startingPosY, 1, 4, '0', barsMoveSpeed, false);
	simulation.TryAddObject(pongBarRight);

	PongBall* pongBall = new PongBall(this, GetWorldSizeX() / 2, GetWorldSizeY() / 2, 2);
	simulation.TryAddObject(pongBall);

}

