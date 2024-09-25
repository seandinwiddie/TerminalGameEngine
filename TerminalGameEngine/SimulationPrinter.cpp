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
    const string& backgroundFileName 
)
    :
    screenSizeX(screenSizeX),
    screenSizeY(screenSizeY),
    padding(screenPadding)
{
    InitBackground(backgroundFileName);
    terminal.Clear();
    
    DrawMargins();
    PrintBackground();
}

void SimulationPrinter::SetHeader(const string& header)
{
    terminal.SetColor(uiColor);
    terminal.SetCursorPosition(0, 0);
    Cout(header);
}

void SimulationPrinter::DrawHorizontalMargin()
{
    string line = "";
    for (int x = 0; x < screenSizeX + 2; ++x)
        line += '-';
    Cout(line);
}

void SimulationPrinter::DrawMargins()
{
    terminal.SetColor(screenMarginsColor);
    terminal.SetCursorPosition(0, 1);
    DrawHorizontalMargin();
    terminal.SetCursorPosition(0, static_cast<int>(GetMaxTerminalY()) );
    DrawHorizontalMargin();

    for (size_t y = MARGIN_OFFSET_TOP_Y; y < GetMaxTerminalY(); ++y)
    {
        terminal.SetCursorPosition(size_t(0), y);
        Cout('|');
        terminal.SetCursorPosition(GetMaxTerminalX(), y);
        Cout('|');
    }
}

void SimulationPrinter::PrintGameOverWindow(const Frame& window)
{
    if (window.GetSizeY() == 0)
        return;

    terminal.SetColor(uiColor);
    for (size_t y = 0; y < screenSizeY; ++y)
    {
        for (size_t x = 0; x < screenSizeX; ++x)
        {
            char c = window.chars[y][x];
            if (c != GAME_OVER_FRAME_IGNORED_CHAR)
            {
                terminal.SetCursorPosition(x + MARGIN_OFFSET_X, y);
                Cout(c);
            }
        }
    }
}

void SimulationPrinter::PrintObject(GameObject* go)
{
    Model model = go->GetModel();
    if (model[0].size() == 0)
        return;
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
    for (int yScreen = GetScreenPos(worldYPos), yModel = 0; yModel < ySize && yScreen < screenSizeY; ++yScreen, ++yModel)
    {
        if (yScreen + MARGIN_OFFSET_TOP_Y < MARGIN_OFFSET_TOP_Y) continue;
        int lineTerminalPosX = GetScreenPos(worldXPos) + MARGIN_OFFSET_X;
        string line = "";

        for (int xScreen = GetScreenPos(worldXPos), xModel = 0; xModel < xSize && xScreen < screenSizeX; ++xScreen, ++xModel)
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
        Cout(line);
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
        Cout(line);
        line.clear();
    }
}

void SimulationPrinter::InitBackground(const string& backgroundFileName)
{
    if (backgroundFileName == "")
    {
        background.ResizeY(0);
        return;
    }
    background.ReadFromFile(backgroundFileName, screenSizeX, screenSizeY);
}

void SimulationPrinter::Cout(const string& s)
{
    std::cout << s;

#if DEBUG_MODE && SHOW_COUT_CALLS
    DEBUG_UpdateCoutCalls();
#endif
}

void SimulationPrinter::Cout(char c)
{
    std::cout << c;

#if DEBUG_MODE && SHOW_COUT_CALLS
    DEBUG_UpdateCoutCalls();
#endif
}

#pragma region ======================================================================== DEBUG
#if DEBUG_MODE

void SimulationPrinter::DEBUG_UpdateCoutCalls()
{
    int startingColor = terminal.GetColor();
    COORD cursorStartingPos = terminal.GetCursorPosition();

    terminal.SetColor(DEBUG_COLOR);
    terminal.SetCursorPosition(0, GetMaxTerminalY() + DEBUG_POSITION_COUT_CALLS);
    //final space makes sure old string is cleared
    string output  = "COUT CALLS: " + std::to_string(DebugManager::Instance().IncreaseCoutCalls()) + string("     ");
    std::cout << output;

    terminal.SetCursorPosition(cursorStartingPos);
    terminal.SetColor(startingColor);
}

void SimulationPrinter::DEBUG_PrintFpsString(size_t fps)
{
    terminal.SetColor(DEBUG_COLOR);
    terminal.SetCursorPosition(0, GetMaxTerminalY() + DEBUG_POSITION_FPS);
    string output = "FPS: " + std::to_string(fps) + '\n';
    std::cout << output;
}

#endif
#pragma endregion