#include "PongLevel.h"
#include "Simulation.h"
#include "PongBar.h"
#include "PongBall.h"

void PongLevel::Load()
{
	Level::Load();
	Simulation& simulation = Simulation::Instance();
	
	char barsChar = 219;
	int startingPosY = GetWorldSizeY() / 2;
	float barsMoveSpeed = 4;
	float ballDeflectFactor = 0.5;

	PongBar* pongBarLeft = new PongBar
	(
		GetScreenPadding()+1, 
		startingPosY, 
		1, 
		4, 
		barsChar, 
		barsMoveSpeed, 
		ballDeflectFactor, 
		true
	);
	simulation.TryAddObject(pongBarLeft);

	PongBar* pongBarRight = new PongBar(
		GetWorldSizeX() - GetScreenPadding() -1, 
		startingPosY, 
		1, 
		4, 
		barsChar, 
		barsMoveSpeed,
		ballDeflectFactor, 
		false
	);
	simulation.TryAddObject(pongBarRight);

	PongBall* pongBall = new PongBall(this, GetWorldSizeX() / 2, GetWorldSizeY() / 2, 4);
	simulation.TryAddObject(pongBall);
}

