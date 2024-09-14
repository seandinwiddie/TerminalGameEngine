#pragma once
#include "Config.h"
#include <vector>
#include <list>
#include <string>

using string = std::string;

class GameObject;

class ScreenManager
{
//---------------------------------------------------------- Fields
private:
	std::vector<std::vector<unsigned char>> frame;
	std::vector<std::vector<std::vector<unsigned char>>> backgrounds;
	std::vector<std::vector<unsigned char>> gameOverScreen;

	int screenSizeX;
	int screenSizeY;
	int padding;
	bool showLevelTime = false;
	int score = -1;
	int bestScore = -1;

#if DEBUG_MODE
	static constexpr double REFRESH_FPS_EVERY_SECONDS = 0.5;
	list<double> fpsRecord;
	double lastTimePrintedFps = 0;
	double shownAverageFps = 0;
#endif

//---------------------------------------------------------- Methods
public:
	ScreenManager(const int sizeX, const int sizeY, const int padding, bool showGameTime,const std::vector<string>& backgroundFileNames = {});

	void Print();
	void InsertGameObject(GameObject* go);
	void InsertString(const string& str, const int y, const int x);
	void Clear();
	bool IsShowingGameOverScreen() const { return score > -1; }
	void ShowGameOverScreen(const int score, const int bestScore);

private:
	void InitBackgrounds(const std::vector<string>& backgroundFilesNames);
	void ReadFrameFromFile(const string& fileName, std::vector<std::vector<unsigned char>>& frame);
	std::vector<std::vector<unsigned char>> GetCurrentBackground() const;
	void InsertGameOverScreenOverFrame();
	bool IsInsideScreenY(const int y) const { return (y >= 0 && y < screenSizeY); }
	bool IsInsideScreenX(const int x) const { return (x >= 0 && x < screenSizeX); }
	bool IsBackgroundEnabled() const { return backgrounds.size() > 0; }
	void ClearScreen();

#if DEBUG_MODE
	void DEBUG_PrintAverageFps(string& frameString);
#endif

};