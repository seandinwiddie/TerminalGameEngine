#include "SpaceInvadersLevel.h"
#include "Simulation.h"
#include "AlienLowScore.h"
#include "AlienMidScore.h"
#include "AlienHighScore.h"
#include "PlayerTank.h"
#include "AliensController.h"
#include "AudioManager.h"
#include "Persistence.h"
#include "UIPrinter.h"

using WindowPosition = UIPrinter::WindowPosition;

int SpaceInvadersLevel::GetWorldSizeX() const
{
	return
		ALIENS_COUNT_X * ALIEN_WIDTH
		+
		(ALIENS_COUNT_X - 1) * SPACE_BETWEEN_ALIENS_X
		+
		2 * ALIENS_SPACE_FROM_MARGINS_X
		+
		2 * GetScreenPadding();
}

void SpaceInvadersLevel::LoadInSimulation()
{
	Level::LoadInSimulation();

	AliensController* aliensController = new AliensController(this, ALIENS_COUNT_X, ALIENS_COUNT_Y);
	Simulation::Instance().TryAddEntity(aliensController);

	LoadAliens(aliensController);
	LoadPlayerTank();
	InitHeader();
}

void SpaceInvadersLevel::NotifyGameOver()
{
	if (IsGameOver())
		return;

	Level::NotifyGameOver();
	AudioManager::Instance().StopMusic();
	AudioManager::Instance().PlayFx("SpaceInv/gameover.wav");
}

void SpaceInvadersLevel::Update()
{
	Level::Update();
}

void SpaceInvadersLevel::OnPostGameOverDelayEnded()
{
	Level::OnPostGameOverDelayEnded();
	int bestScore = Persistence::GetBestScoreComparingToNewOne(GetPersistenceFilePath(), score);
	ShowGameOverScreen(score, bestScore);
	AudioManager::Instance().PlayFx("SpaceInv/showEndScreen.wav");
}

void SpaceInvadersLevel::ShowGameOverScreen(int score, int bestScore)
{
	string messageEnding = score > bestScore ? "new record!" : ("best: " + std::to_string(bestScore));
	string message = "you survived for " + std::to_string(score) + " seconds, " + messageEnding;

	//center message
	string leftSpacing = "";
	for (int i = 0; i < (42 - message.size()) / 2; ++i)
		leftSpacing += " ";
	message = leftSpacing + message;

	gameOverWindow.ReplaceChar(message, '$');

	Simulation::Instance().GetUIPrinter().PrintWindow(gameOverWindow, Terminal::WHITE, WindowPosition::CenterX_CenterY);
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
	string scoreString = "score: " + std::to_string(score);
	int xPos = Simulation::Instance().GetScreenSizeX() / 2 - scoreString.size()/2;
	Simulation::Instance().GetUIPrinter().PrintOnHeader(scoreString, xPos, Terminal::WHITE);
}

void SpaceInvadersLevel::PrintHealth()
{
	// 1 because of left margin
	int xPos = 1;

	string healthStr = "";
	for (int i = 0; i < health; i++)
		healthStr += "<3 ";

	Simulation::Instance().GetUIPrinter().PrintOnHeader(healthStr, xPos, Terminal::RED);
}

void SpaceInvadersLevel::PrintWave()
{
	int xPos = GetScreenMaxX();
	string waveStr = "wave: " + std::to_string(waveNumber);
	xPos -= waveStr.length();
	Simulation::Instance().GetUIPrinter().PrintOnHeader(waveStr, xPos, Terminal::WHITE);
}


void SpaceInvadersLevel::LoadPlayerTank()
{
	int xPos = GetWorldSizeX() / 2;
	int yPos = GetScreenPadding();
	PlayerTank* playerTank = new PlayerTank(xPos, yPos);
	Simulation::Instance().TryAddEntity(playerTank);
}

void SpaceInvadersLevel::LoadAliens(AliensController* controller)
{
	int yPos = GetScreenMaxY() - ALIENS_SPACE_FROM_TOP_MARGIN - ALIEN_HEIGHT;
	int yIndex = 0;
	while (yIndex < ALIENS_COUNT_Y)
	{
		AddAliensRowToSimulation(yPos, yIndex, controller);
		yPos -= (ALIEN_HEIGHT + SPACE_BETWEEN_ALIENS_Y);
		++yIndex;
	}
}

const type_info& SpaceInvadersLevel::GetAlienTypeForRow(int yIndex)
{
	if (yIndex == 0)
		return typeid(AlienHighScore);
	else if (yIndex < 3)
		return typeid(AlienMidScore);
	else
		return typeid(AlienLowScore);
}

void SpaceInvadersLevel::AddAliensRowToSimulation(int yPos, int yIndex, AliensController* controller)
{
	int xPos = GetScreenPadding() + ALIENS_SPACE_FROM_MARGINS_X;
	const type_info& alienType = GetAlienTypeForRow(yIndex);
	int xIndex = 0;
	while (xIndex < ALIENS_COUNT_X)
	{
		Alien* alien = CreateAlienOfType(alienType,xPos,yPos, xIndex, yIndex);
		Simulation::Instance().TryAddEntity(alien);
		controller->RegisterAlien(alien, xIndex, yIndex);

		++xIndex;
		xPos += ALIEN_WIDTH + SPACE_BETWEEN_ALIENS_X;
	}
}

Alien* SpaceInvadersLevel::CreateAlienOfType(const type_info& alienType, int xPos, int yPos, int xIndex, int yIndex)
{
	if (alienType == typeid(AlienHighScore))
		return new AlienHighScore(xPos, yPos, xIndex, yIndex);
	else if (alienType == typeid(AlienMidScore))
		return new AlienMidScore(xPos, yPos, xIndex, yIndex);
	else if (alienType == typeid(AlienLowScore))
		return new AlienLowScore(xPos, yPos, xIndex, yIndex);
	else
		throw std::invalid_argument("invalid alien type receiveds");
}