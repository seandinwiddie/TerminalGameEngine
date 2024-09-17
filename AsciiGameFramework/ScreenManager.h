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
//---------------------------------------------------------- Settings
private:
	static const char UI_MESSAGE_FRAME_IGNORED_CHAR = '#';

//---------------------------------------------------------- Fields
private:
	Frame frame;
	std::vector<Frame> backgrounds;

	uint screenSizeX;
	uint screenSizeY;
	uint padding;
	bool showTimeUI = false;
	bool isShowingUIMessage;
	Frame frameUIMessage;

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

	void PrintFrameOnTerminal();
	static void ClearTerminal();
	void InsertGameObject(TransformObject* go);
	void ClearFrame();
	uint GetScreenSizeX() const { return screenSizeX; }
	uint GetScreenSizeY() const { return screenSizeY; }
	void SetUIMessage(Frame UIMessage){ this->frameUIMessage = UIMessage; }

private:
	void InsertUIMessageOverFrame();
	void InitBackgrounds(const std::vector<string>& backgroundFilesNames);
	Frame GetCurrentBackground() const;
	bool IsBackgroundEnabled() const { return backgrounds.size() > 0; }

//---------------------------------------------------------- Debug
#if DEBUG_MODE
private:
	static constexpr double REFRESH_FPS_EVERY_SECONDS = 0.5;
	std::list<double> fpsRecord;
	double lastTimePrintedFps = 0;
	double shownAverageFps = 0;

	void DEBUG_PrintAverageFps(string& frameString);
#endif

};