#include "PongLevel.h"
#include "Simulation.h"
#include "PongBar.h"
#include "PongBall.h"
#include "AudioManager.h"
#include "UIPrinter.h"

size_t PongLevel::scorePlayer1 = 0;
size_t PongLevel::scorePlayer2 = 0;

void PongLevel::LoadInSimulation()
{
	Level::LoadInSimulation();
	Simulation& simulation = Simulation::Instance();

	//--------------- bars general settings
	char barsChar = -37;
	int startingPosX = GetWorldSizeX() / 2 - 1;
	int barsSize = 8;
	double barsMoveSpeed = 32;
	double deflectFactor = 2.5;

	//--------------- bottom bar
	PongBar* bottomBar = new PongBar
	(
		startingPosX,
		GetScreenPadding(), 
		barsSize,
		1,
		barsChar, 
		barsMoveSpeed, 
		deflectFactor, 
		true
	);
	simulation.TryAddEntity(bottomBar);

	//--------------- top bar
	PongBar* topBar = new PongBar(
		startingPosX,
		GetWorldSizeY() - GetScreenPadding() -1, 
		barsSize,
		1,
		barsChar, 
		barsMoveSpeed,
		deflectFactor, 
		false
	);
	simulation.TryAddEntity(topBar);
	
	//--------------- ball
	double ballSpeed = 16;
	PongBall* pongBall = new PongBall(this, GetWorldSizeX() / 2, GetWorldSizeY() / 2, ballSpeed);
	simulation.TryAddEntity(pongBall);
	RefreshHeader();
}

void PongLevel::IncreaseP1Score()
{
	++scorePlayer1;
	RefreshHeader();
}

void PongLevel::IncreaseP2Score()
{
	++scorePlayer2;
	RefreshHeader();
}

void PongLevel::RefreshHeader()
{
	Simulation::Instance().GetUIPrinter().
		PrintOnHeader(std::to_string(scorePlayer1) + " - " + std::to_string(scorePlayer2),0,Terminal::WHITE);
}

void PongLevel::OnPostGameOverDelayEnded()
{ 
	Level::OnPostGameOverDelayEnded();
	Terminate();
}

void PongLevel::NotifyGameOver()
{ 
	Level::NotifyGameOver();
	AudioManager::Instance().PlayFx("Pong/goal.wav"); 
}