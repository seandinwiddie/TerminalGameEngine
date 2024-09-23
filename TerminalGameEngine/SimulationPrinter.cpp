#include "SimulationPrinter.h"

#include "GameObject.h"
#include "Simulation.h"
#include "Config.h"
#include "Level.h"
#include "TimeHelper.h"
#include "Terminal.h"

#include <windows.h>
#include <cassert>
#include <algorithm>

SimulationPrinter::SimulationPrinter
(
    uint screenSizeX, 
    uint screenSizeY, 
    uint screenPadding, 
    const string& backgroundFileName 
)
    :
    screenSizeX(screenSizeX),
    screenSizeY(screenSizeY),
    padding(screenPadding)
{
    UIFrame.Clear();
    InitBackground(backgroundFileName);
    terminal.Clear();
    
    DrawMargins();
    PrintBackground();

#if DEBUG_MODE
    fpsRecord.clear();
    fpsRecord.resize(0);
#endif
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
    terminal.SetCursorPosition(0, GetMaxTerminalY());
    DrawHorizontalMargin();

    for (int y = MARGIN_OFFSET_Y; y < GetMaxTerminalY(); ++y)
    {
        terminal.SetCursorPosition(0, y);
        Cout('|');
        terminal.SetCursorPosition(GetMaxTerminalX(), y);
        Cout('|');
    }
}

void SimulationPrinter::PrintUIFrame(const Frame& UIMessage)
{
    this->UIFrame = UIMessage;
    if (UIFrame.GetSizeY() == 0)
        return;

    terminal.SetColor(uiColor);
    for (int y = 0; y < screenSizeY; ++y)
    {
        for (int x = 0; x < screenSizeX; ++x)
        {
            char c = UIFrame.chars[y][x];
            if (c != UI_MESSAGE_FRAME_IGNORED_CHAR)
            {
                terminal.SetCursorPosition(x + MARGIN_OFFSET_X, y);
                Cout(c);
            }
        }
    }
}

void SimulationPrinter::PrintObject(GameObject* go)
{
    std::vector<std::vector<char>> model = go->GetModel();
    if (model[0].size() == 0)
        return;
    terminal.SetColor(go->GetColor());
    PrintInternal(go->GetPosX(), go->GetPosY(), go->GetModelWidth(), go->GetModelHeight(), go);
}

void SimulationPrinter::ClearObject(GameObject* obj)
{
    PrintInternal(obj->GetPosX(), obj->GetPosY(), obj->GetModelWidth(), obj->GetModelHeight(), nullptr);
}

void SimulationPrinter::ClearArea(int worldXPos, int worldYPos, uint xSize, uint ySize)
{
    PrintInternal(worldXPos, worldYPos, xSize, ySize, nullptr);
}

void SimulationPrinter::PrintInternal(int worldXPos, int worldYPos, uint xSize, uint ySize, GameObject* go)
{
    terminal.SetColor(go == nullptr ? backgroundColor : go->GetColor());
    for (int yScreen = GetScreenPos(worldYPos), yModel = 0; yModel < ySize && yScreen < screenSizeY; ++yScreen, ++yModel)
    {
        if (yScreen + MARGIN_OFFSET_Y < MARGIN_OFFSET_Y) continue;
        int lineStartPosX = GetScreenPos(worldXPos);
        string line = "";

        for (int xScreen = lineStartPosX, xModel = 0; xModel < xSize && xScreen < screenSizeX; ++xScreen, ++xModel)
        {
            if (xScreen + MARGIN_OFFSET_X < MARGIN_OFFSET_X)continue;

            if (go == nullptr)
                line += background.IsSetup() ? background.chars[yScreen][xScreen] : ' ';
            else
                line += go->GetModel()[yModel][xModel];
        }
        if (lineStartPosX + MARGIN_OFFSET_X < MARGIN_OFFSET_X)
            lineStartPosX = MARGIN_OFFSET_X;
        terminal.SetCursorPosition(lineStartPosX, screenSizeY - yScreen + MARGIN_OFFSET_Y_NEW);
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
            char charToPrint = background.chars[screenSizeY - y -1][x];
            line += charToPrint;
        }
        terminal.SetCursorPosition(MARGIN_OFFSET_X, y + MARGIN_OFFSET_Y);
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
    background.ReadFrameFromFile(backgroundFileName, screenSizeX, screenSizeY);
}

void SimulationPrinter::Cout(const string& s)
{
    std::cout << s;

#if DEBUG_MODE && SHOW_COUT_CALLS
    DEBUG_IncreaseCoutCallsCount();
#endif
}

void SimulationPrinter::Cout(char c)
{
    std::cout << c;

#if DEBUG_MODE && SHOW_COUT_CALLS
    DEBUG_IncreaseCoutCallsCount();
#endif
}

#pragma region ======================================================================== DEBUG
#if DEBUG_MODE

void SimulationPrinter::DEBUG_IncreaseCoutCallsCount()
{
    int startingColor = terminal.GetColor();
    terminal.SetColor(debugColor);
    COORD cursorStartingPos = terminal.GetCursorPosition();

    terminal.SetCursorPosition(0, GetMaxTerminalY() + 4);
    std::cout << "                  ";
    terminal.SetCursorPosition(0, GetMaxTerminalY() + 4);
    std::cout << "COUT CALLS: " << coutCalls++;

    if (coutCalls == 1000)
        coutCalls = 0;

    terminal.SetCursorPosition(cursorStartingPos);
    terminal.SetColor(startingColor);
}

void SimulationPrinter::DEBUG_PrintAverageFps()
{
    double fps = TimeHelper::Instance().GetFPS();
    fpsRecord.push_back(fps);

    if (TimeHelper::Instance().GetTime() - lastTimePrintedFps > REFRESH_FPS_EVERY_SECONDS)
    {
        shownAverageFps = 0;

        for (double fps : fpsRecord)
            shownAverageFps += fps;
        shownAverageFps /= fpsRecord.size();

        fpsRecord.clear();
        lastTimePrintedFps = TimeHelper::Instance().GetTime();
    }
    string fpsString = "FPS: " + std::to_string(static_cast<int>(shownAverageFps)) + '\n';

    terminal.SetColor(debugColor);
    terminal.SetCursorPosition(0, GetMaxTerminalY() + 3);
    std::cout << fpsString;
}

#endif
#pragma endregion