#include "SpaceInvadersLevel.h"
#include "Simulation.h"
#include "AlienLowScore.h"
#include "AlienMidScore.h"
#include "AlienHighScore.h"

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
		const type_info& type = GetTypeOfAlienForRow(addedRows);
		AddAliensRowToSimulation(yPos,type);
		yPos -= (ALIEN_HEIGHT + SPACE_BETWEEN_ALIENS_Y);
		++addedRows;
	}
}

const type_info& SpaceInvadersLevel::GetTypeOfAlienForRow(int rowIndexFromTop)
{
	if (rowIndexFromTop == 0)
		return typeid(AlienHighScore);
	else if (rowIndexFromTop < 3)
		return typeid(AlienMidScore);
	else
		return typeid(AlienLowScore);
}

void SpaceInvadersLevel::AddAliensRowToSimulation(int yPos, const type_info& alienType)
{
	Simulation& simulation = Simulation::Instance();

	int xPos = GetScreenPadding() + ALIENS_SPACE_FROM_MARGINS_X;
	int addedAliens = 0;
	while (addedAliens < ALIENS_COLUMNS_COUNT)
	{
		Alien* alien;

		if (alienType == typeid(AlienHighScore))
			alien = new AlienHighScore(xPos, yPos);
		else if (alienType == typeid(AlienMidScore))
			alien = new AlienMidScore(xPos, yPos);
		else if (alienType == typeid(AlienLowScore))
			alien = new AlienLowScore(xPos, yPos);
		else
			throw std::invalid_argument("invalid alien type receiveds");
		
		simulation.TryAddEntity(alien);
		++addedAliens;
		xPos += ALIEN_WIDTH + SPACE_BETWEEN_ALIENS_X;
	}
}