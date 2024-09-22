#include "PongLevel.h"
#include "Simulation.h"
#include "PongBar.h"
#include "PongBall.h"

uint PongLevel::scorePlayer1 = 0;
uint PongLevel::scorePlayer2 = 0;

void PongLevel::LoadInSimulation()
{
	Level::LoadInSimulation();
	Simulation& simulation = Simulation::Instance();

	char barsChar = 219;
	int startingPosY = GetWorldSizeY() / 2 - 1;
	int barsSize = 4;
	float barsMoveSpeed = 32;
	float ballDeflectFactor = 0.5;

	PongBar* pongBarLeft = new PongBar
	(
		GetScreenPadding()+1, 
		startingPosY, 
		1, 
		barsSize,
		barsChar, 
		barsMoveSpeed, 
		ballDeflectFactor, 
		true
	);
	simulation.TryAddEntity(pongBarLeft);

	PongBar* pongBarRight = new PongBar(
		GetWorldSizeX() - GetScreenPadding() -1, 
		startingPosY, 
		1, 
		barsSize,
		barsChar, 
		barsMoveSpeed,
		ballDeflectFactor, 
		false
	);
	simulation.TryAddEntity(pongBarRight);

	PongBall* pongBall = new PongBall(this, GetWorldSizeX() / 2, GetWorldSizeY() / 2, 32);
	simulation.TryAddEntity(pongBall);
}

void PongLevel::Update()
{
	Level::Update();
	Simulation::Instance().SetTerminalHeader(std::to_string(scorePlayer1)+" - "+ std::to_string(scorePlayer2));
}

