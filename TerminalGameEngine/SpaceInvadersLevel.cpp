#include "SpaceInvadersLevel.h"
#include "Simulation.h"
#include "AlienLowScore.h"
#include "AlienMidScore.h"
#include "AlienHighScore.h"
#include "PlayerTank.h"

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

	LoadAliens();
	LoadPlayerTank();
	InitHeader();
}

void SpaceInvadersLevel::NotifyGameOver()
{

}

void SpaceInvadersLevel::Update()
{

}

void SpaceInvadersLevel::IncreasePlayerScore(size_t increment)
{ 
	score += increment; 
	PrintScore();
}

void SpaceInvadersLevel::InitHeader()
{
	PrintScore();
	PrintHealth();
	PrintWave();
}

void SpaceInvadersLevel::PrintScore()
{
	int xPos = Simulation::Instance().GetScreenSizeX() / 2;
	Simulation::Instance().GetUIPrinter().PrintOnHeader("score: " + std::to_string(score), xPos, Terminal::WHITE);
}

void SpaceInvadersLevel::PrintHealth()
{
	int xPos = 0;

	string healthStr = "";
	for (int i = 0; i < health; i++)
		healthStr += "<3 ";

	Simulation::Instance().GetUIPrinter().PrintOnHeader(healthStr, xPos, Terminal::RED);
}

void SpaceInvadersLevel::PrintWave()
{
	int xPos = GetScreenMaxX();
	string waveStr = "wave: " + std::to_string(wave);
	xPos -= waveStr.length() - 2;

	Simulation::Instance().GetUIPrinter().PrintOnHeader(waveStr, xPos, Terminal::WHITE);
}

void SpaceInvadersLevel::OnPostGameOverDelayEnded()
{

}

void SpaceInvadersLevel::ShowGameOverScreen()
{
	// mostrare pannello con victory / defeat
}

void SpaceInvadersLevel::LoadPlayerTank()
{
	int xPos = GetWorldSizeX() / 2;
	int yPos = GetScreenPadding();
	PlayerTank* playerTank = new PlayerTank(xPos, yPos);
	Simulation::Instance().TryAddEntity(playerTank);
}

void SpaceInvadersLevel::LoadAliens()
{
	int yPos = GetScreenMaxY() - ALIENS_SPACE_FROM_TOP_MARGIN - ALIEN_HEIGHT;
	int addedRows = 0;
	while (addedRows < ALIENS_ROWS_COUNT)
	{
		const type_info& type = GetAlienTypeForRow(addedRows);
		AddAliensRowToSimulation(yPos,type);
		yPos -= (ALIEN_HEIGHT + SPACE_BETWEEN_ALIENS_Y);
		++addedRows;
	}
}

const type_info& SpaceInvadersLevel::GetAlienTypeForRow(int rowIndex)
{
	if (rowIndex == 0)
		return typeid(AlienHighScore);
	else if (rowIndex < 3)
		return typeid(AlienMidScore);
	else
		return typeid(AlienLowScore);
}

void SpaceInvadersLevel::AddAliensRowToSimulation(int yPos, const type_info& alienType)
{
	int xPos = GetScreenPadding() + ALIENS_SPACE_FROM_MARGINS_X;
	int addedAliens = 0;
	while (addedAliens < ALIENS_COLUMNS_COUNT)
	{
		Alien* alien = CreateAlienOfType(alienType,xPos,yPos);
		Simulation::Instance().TryAddEntity(alien);
		++addedAliens;
		xPos += ALIEN_WIDTH + SPACE_BETWEEN_ALIENS_X;
	}
}

Alien* SpaceInvadersLevel::CreateAlienOfType(const type_info& alienType, int xPos, int yPos)
{
	if (alienType == typeid(AlienHighScore))
		return new AlienHighScore(xPos, yPos);
	else if (alienType == typeid(AlienMidScore))
		return new AlienMidScore(xPos, yPos);
	else if (alienType == typeid(AlienLowScore))
		return new AlienLowScore(xPos, yPos);
	else
		throw std::invalid_argument("invalid alien type receiveds");
}