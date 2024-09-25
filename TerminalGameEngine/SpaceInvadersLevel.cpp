#include "SpaceInvadersLevel.h"
#include "Simulation.h"
#include "AlienLowScore.h"

int SpaceInvadersLevel::GetWorldSizeX() const
{
	return
		ALIENS_COLUMNS_COUNT * ALIEN_WIDTH
		+
		(ALIENS_COLUMNS_COUNT - 1) * SPACE_BETWEEN_ALIENS_X
		+
		2 * ALIENS_SPACE_FROM_MARGINS_X
		+
		2 * GetScreenPadding();
}

void SpaceInvadersLevel::LoadInSimulation()
{
	Level::LoadInSimulation();
	Simulation& simulation = Simulation::Instance();

	//--------------- bars general settings
	AddAliensToSimulation();
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

void SpaceInvadersLevel::AddAliensToSimulation()
{
	Simulation& simulation = Simulation::Instance();

	int yPos = GetScreenMaxY() - ALIENS_SPACE_FROM_TOP_MARGIN - ALIEN_HEIGHT;
	int addedRows = 0;
	while (addedRows < ALIENS_ROWS_COUNT)
	{
		AddAliensRowToSimulation(yPos);
		yPos -= (ALIEN_HEIGHT + SPACE_BETWEEN_ALIENS_Y);
		++addedRows;
	}
}

void SpaceInvadersLevel::AddAliensRowToSimulation(int yPos)
{
	Simulation& simulation = Simulation::Instance();

	int xPos = GetScreenPadding() + ALIENS_SPACE_FROM_MARGINS_X;
	int addedAliens = 0;
	while (addedAliens < ALIENS_COLUMNS_COUNT)
	{
		Alien* alien = new AlienLowScore(xPos, yPos);
		simulation.TryAddEntity(alien);
		++addedAliens;
		xPos += ALIEN_WIDTH + SPACE_BETWEEN_ALIENS_X;
	}
}