#pragma once
#include "Config.h"
#include "Frame.h"
#include "Terminal.h"
#include "Printer.h"
#include <vector>
#include <list>
#include <string>

using string = std::string;

class GameObject;

class SimulationPrinter : public Printer
{
	int backgroundColor = Terminal::BLUE_DARK;
	Frame background;
//---------------------------------------------------------- Methods
public:
	SimulationPrinter
	(
		size_t screenSizeX,
		size_t screenSizeY,
		size_t screenPadding,
		const string& backgroundFileName = ""
	);

	void PrintObject(GameObject* obj);
	void ClearObject(GameObject* obj);
	void ClearArea(int worldXPos, int worldYPos, size_t xSize, size_t ySize);
	void SetBackgroundColor(int color) { backgroundColor = color; }

private:
	void PrintInternal(int worldXPos, int worldYPos, size_t xSize, size_t ySize, GameObject* go);
	void InitBackground(const string& backgroundFileName);
	void PrintBackground();
};