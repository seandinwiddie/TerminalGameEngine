#include "SpaceInvadersLevel.h"
#include "Simulation.h"
#include "Alien.h"

void SpaceInvadersLevel::LoadInSimulation()
{
	Level::LoadInSimulation();
	Simulation& simulation = Simulation::Instance();

	//--------------- bars general settings

	Alien* alien = new Alien(0, 0);
	simulation.TryAddEntity(alien);
}

void SpaceInvadersLevel::NotifyGameOver()
{

}

void SpaceInvadersLevel::Update()
{

}

void SpaceInvadersLevel::OnPostGameOverDelayEnded()
{

}

void SpaceInvadersLevel::ShowGameOverScreen()
{
	// mostrare pannello con victory / defeat
}