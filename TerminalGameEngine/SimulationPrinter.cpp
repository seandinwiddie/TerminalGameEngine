#include "SimulationPrinter.h"

#include "GameObject.h"
#include "Simulation.h"
#include "Config.h"
#include "Level.h"
#include "TimeHelper.h"
#include "Terminal.h"
#include "DebugManager.h"

#include <Windows.h>
#include <cassert>
#include <algorithm>

SimulationPrinter::SimulationPrinter
(
    size_t screenSizeX, 
    size_t screenSizeY, 
    size_t screenPadding, 
    int backgroundColor,
    const string& backgroundFileName 
) : Printer(screenSizeX, screenSizeY, screenPadding), backgroundColor(backgroundColor)
{
    InitBackground(backgroundFileName);
}

void SimulationPrinter::PrintObject(GameObject* go)
{
    Model model = go->GetModel();
    assert(model.size() > 0 && model[0].size() > 0);
    terminal.SetColor(go->GetColor());
    PrintInternal(go->GetPosX(), go->GetPosY(), go->GetModelWidth(), go->GetModelHeight(), go);
}

void SimulationPrinter::ClearObject(GameObject* obj)
{
    PrintInternal(obj->GetPosX(), obj->GetPosY(), obj->GetModelWidth(), obj->GetModelHeight(), nullptr);
}

void SimulationPrinter::ClearArea(int worldXPos, int worldYPos, size_t xSize, size_t ySize)
{
    PrintInternal(worldXPos, worldYPos, xSize, ySize, nullptr);
}

void SimulationPrinter::PrintInternal(int worldXPos, int worldYPos, size_t xSize, size_t ySize, GameObject* go)
{
    terminal.SetColor(go == nullptr ? backgroundColor : go->GetColor());
    for (int yScreen = ConvertWorldPosToScreenPos(worldYPos), yModel = 0; yModel < ySize && yScreen < screenSizeY; ++yScreen, ++yModel)
    {
        if (yScreen + MARGIN_OFFSET_TOP_Y < MARGIN_OFFSET_TOP_Y) continue;
        int lineTerminalPosX = ConvertWorldPosToScreenPos(worldXPos) + MARGIN_OFFSET_X;
        string line = "";

        for (int xScreen = ConvertWorldPosToScreenPos(worldXPos), xModel = 0; xModel < xSize && xScreen < screenSizeX; ++xScreen, ++xModel)
        {
            if (xScreen + MARGIN_OFFSET_X < MARGIN_OFFSET_X)continue;

            if (go == nullptr)
                line += background.IsSetup() ? background.chars[yScreen][xScreen] : ' ';
            else
                line += go->GetModel()[yModel][xModel];
        }
        if (lineTerminalPosX < MARGIN_OFFSET_X)
            lineTerminalPosX = MARGIN_OFFSET_X;
        terminal.SetCursorPosition(lineTerminalPosX, screenSizeY - yScreen + MARGIN_OFFSET_BOTTOM_Y);
        terminal.Cout(line);
    }
}

void SimulationPrinter::PrintBackground()
{
    if (!background.IsSetup())
        return;

    terminal.SetColor(backgroundColor);

    string line = "";
    for (int y = 0; y < screenSizeY; ++y)
    {
        for (int x = 0; x < screenSizeX; ++x)
        {
            //reversing y order
            char charToPrint = background.chars[screenSizeY - y - MARGIN_OFFSET_BOTTOM_Y][x];
            line += charToPrint;
        }
        terminal.SetCursorPosition(MARGIN_OFFSET_X, y + MARGIN_OFFSET_TOP_Y);
        terminal.Cout(line);
        line.clear();
    }
}

void SimulationPrinter::InitBackground(const string& backgroundFileName)
{
    if (backgroundFileName == "")
    {
        background.SetEmpty(0);
        return;
    }
    background.ReadFromFile(backgroundFileName);
    PrintBackground();
}