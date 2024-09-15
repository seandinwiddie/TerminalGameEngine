#pragma once
#include "Config.h"
#include <vector>
#include <list>
#include <string>

using string = std::string;

class TransformObject;

class ScreenManager
{
//---------------------------------------------------------- Fields
private:
	std::vector<std::vector<unsigned char>> frame;
	std::vector<std::vector<std::vector<unsigned char>>> backgrounds;

	int screenSizeX; //todo read from simulation
	int screenSizeY;
	int padding;
	bool showLevelTime = false;
	bool isShowingUIMessage;
	std::vector<std::vector<unsigned char>> UIMessage = {{}};

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
	void InsertGameObject(TransformObject* go);
	void Clear();
	int GetScreenSizeX() const { return screenSizeX; }
	int GetScreenSizeY() const { return screenSizeY; }
	void SetUIMessage(std::vector<std::vector<unsigned char>> UIMessage){ this->UIMessage = UIMessage; }

private:
	void InsertUIMessageOverFrame();
	void InitBackgrounds(const std::vector<string>& backgroundFilesNames);
	std::vector<std::vector<unsigned char>> GetCurrentBackground() const;
	bool IsInsideScreenY(const int y) const { return (y >= 0 && y < screenSizeY); }
	bool IsInsideScreenX(const int x) const { return (x >= 0 && x < screenSizeX); }
	bool IsBackgroundEnabled() const { return backgrounds.size() > 0; }
	void ClearScreen();


#if DEBUG_MODE
	void DEBUG_PrintAverageFps(string& frameString);
#endif

};