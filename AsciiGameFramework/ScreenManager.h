#pragma once
#include "Config.h"
#include "Frame.h"
#include <vector>
#include <list>
#include <string>

using string = std::string;

class TransformObject;

class ScreenManager
{
//---------------------------------------------------------- Fields
private:
	Frame frame;
	std::vector<Frame> backgrounds;

	uint screenSizeX;
	uint screenSizeY;
	uint padding;
	bool showTimeUI = false;
	bool isShowingUIMessage;
	Frame UIMessage;

#if DEBUG_MODE
	static constexpr double REFRESH_FPS_EVERY_SECONDS = 0.5;
	list<double> fpsRecord;
	double lastTimePrintedFps = 0;
	double shownAverageFps = 0;
#endif

//---------------------------------------------------------- Methods
public:
	ScreenManager
	(
		const uint worldSizeX,
		const uint worldSizeY,
		const uint padding, 
		bool showTimeUI,
		const std::vector<string>& backgroundFileNames = {}
	);

	void Print();
	void InsertGameObject(TransformObject* go);
	void Clear();
	int GetScreenSizeX() const { return screenSizeX; }
	int GetScreenSizeY() const { return screenSizeY; }
	void SetUIMessage(Frame UIMessage){ this->UIMessage = UIMessage; }
	static void ClearScreen();

private:
	void InsertUIMessageOverFrame();
	void InitBackgrounds(const std::vector<string>& backgroundFilesNames);
	Frame GetCurrentBackground() const;
	bool IsInsideScreenY(const int y) const { return (y >= 0 && y < screenSizeY); }
	bool IsInsideScreenX(const int x) const { return (x >= 0 && x < screenSizeX); }
	bool IsBackgroundEnabled() const { return backgrounds.size() > 0; }

#if DEBUG_MODE
	void DEBUG_PrintAverageFps(string& frameString);
#endif

};