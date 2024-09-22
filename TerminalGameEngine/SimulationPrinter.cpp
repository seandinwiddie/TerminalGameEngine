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
    const std::vector<string>& backgroundFileNames 
)
    : 
    screenSizeX(screenSizeX),
    screenSizeY(screenSizeY),
    padding(screenPadding)
{
    header = "";
    frameUIMessage.Clear();
    InitBackgrounds(backgroundFileNames);
    terminal.Clear();

    DrawMargins();
    PrintBackground();

#if DEBUG_MODE
    fpsRecord.clear();
    fpsRecord.resize(0);
#endif
}

//void SimulationPrinter::PrintUI()
//{
//#if DEBUG_MODE
//    DEBUG_PrintAverageFps();
//#endif
//
//    string headerNewLine = header + '\n';
//    InsertInPrintBuffer(headerNewLine, uiColor);
//
//    PrintUIMessageOnFrame();
//
//    //print frame
//    for (int m = screenSizeY - 1; m >= 0; --m)
//    {
//        InsertVerticalMarginChar(false);
//        string lineStr = "";
//        for (int n = 0; n < screenSizeX; ++n)
//        {
//            int cellColor = frame.colors[m][n];
//            char cellChar = frame.chars[m][n];
//            InsertInPrintBuffer(cellChar, cellColor);
//        }
//        InsertVerticalMarginChar(true);
//    }
//
//    InsertHorizontalMarginLine();
//
//    AddPrintBufferToOperations();
//    terminal.Clear();
//    for (PrintOperation operation : printOperations)
//    {
//        terminal.SetColor(operation.color);
//        std::cout << operation.str;
//    }
//    printOperations.clear();
//}
//

void SimulationPrinter::DrawHorizontalMargin()
{
    for (int x = 0; x < screenSizeX + 2; ++x)
        std::cout << '-';
}

void SimulationPrinter::PrintUIMessageOnFrame()
{
    if (frameUIMessage.GetSizeY() == 0)
        return;

    terminal.SetColor(uiColor);
    for (int y = 0; y < screenSizeY; ++y)
        for (int x = 0; x < screenSizeX; ++x)
        {
            char c = frameUIMessage.chars[y][x];
            if (c != UI_MESSAGE_FRAME_IGNORED_CHAR)
            {
                terminal.SetCursorPosition(x, y);
                //todo could be optimized doing cout of strings for adjacent characters (also in other methods)
                std::cout << c;
            }
        }
}

void SimulationPrinter::DrawMargins()
{
    terminal.SetColor(screenMarginsColor);
    terminal.SetCursorPosition(0, 0);
    DrawHorizontalMargin();
    terminal.SetCursorPosition(0, GetMaxTerminalY());
    DrawHorizontalMargin();

    for (int y = MARGIN_OFFSET_Y; y < GetMaxTerminalY(); ++y)
    {
        terminal.SetCursorPosition(0, y);
        std::cout << "|";
        terminal.SetCursorPosition(GetMaxTerminalX(), y);
        std::cout << "|";
    }
}

void SimulationPrinter::PrintObject(GameObject* go)
{
    std::vector<std::vector<char>> model = go->GetModel();
    if (model[0].size() == 0)
        return;

    terminal.SetColor(go->GetColor());

    for (int yScreen = GetScreenPos(go->GetPosY()) + MARGIN_OFFSET_Y, yModel = 0; yModel < go->GetModelHeight() && yScreen < GetMaxTerminalY(); ++yScreen, ++yModel)
    {
        if (yScreen < MARGIN_OFFSET_Y)
            continue;
        for (int xScreen = GetScreenPos(go->GetPosX()) + MARGIN_OFFSET_X, xModel = 0; xModel < go->GetModelWidth() && xScreen < GetMaxTerminalX(); ++xScreen, ++xModel)
        {
            if (xScreen < MARGIN_OFFSET_X)
                continue;
            char charToPrint = go->GetModel()[yModel][xModel];
            terminal.SetCursorPosition(xScreen, GetMaxTerminalY() - yScreen);
            std::cout << charToPrint;
        }
    }
}

void SimulationPrinter::PrintBackground()
{
    if (!IsBackgroundEnabled())
        return;

    terminal.SetColor(backgroundColor);

    for (int yScreen =  MARGIN_OFFSET_Y; yScreen < GetMaxTerminalY(); ++yScreen)
    {
        for (int xScreen = MARGIN_OFFSET_X; xScreen < GetMaxTerminalX(); ++xScreen)
        {
            char charToPrint = GetCurrentBackground().chars[yScreen - MARGIN_OFFSET_Y][xScreen-MARGIN_OFFSET_X];
            terminal.SetCursorPosition(xScreen, GetMaxTerminalY() - yScreen);
            std::cout << charToPrint;
        }
    }
}

void SimulationPrinter::Clear(int worldXPos, int worldYPos, uint xSize, uint ySize)
{
    for (int yScreen = GetScreenPos(worldYPos) + MARGIN_OFFSET_Y, yModel = 0; yModel < ySize && yScreen < GetMaxTerminalY(); ++yScreen, ++yModel)
    {
        if (yScreen < MARGIN_OFFSET_Y)
            continue;
        for (int xScreen = GetScreenPos(worldXPos) + MARGIN_OFFSET_X, xModel = 0; xModel < xSize && xScreen < GetMaxTerminalX(); ++xScreen, ++xModel)
        {
            if (xScreen < MARGIN_OFFSET_X)
                continue;
            terminal.SetColor(backgroundColor);
            char charToPrint = IsBackgroundEnabled() ? GetCurrentBackground().chars[yScreen-MARGIN_OFFSET_Y][xScreen-MARGIN_OFFSET_X] : ' ';
            terminal.SetCursorPosition(xScreen, GetMaxTerminalY() - yScreen);
            std::cout << charToPrint;
        }
    }
}

void SimulationPrinter::Clear(GameObject* obj)
{
    Clear(obj->GetPosX(), obj->GetPosY(), obj->GetModelWidth(), obj->GetModelHeight());
}


void SimulationPrinter::InitBackgrounds(const std::vector<string>& backgroundFilesNames)
{
    if (backgroundFilesNames.size() == 0)
    {
        backgrounds.resize(0);
        return;
    }

    backgrounds.resize(backgroundFilesNames.size());

    for (int i = 0; i < backgroundFilesNames.size(); i++)
        backgrounds[i].ReadFrameFromFile(backgroundFilesNames[i], screenSizeX, screenSizeY);
}

Frame SimulationPrinter::GetCurrentBackground()const
{
    return  TimeHelper::Instance().IsTimeForFirstOfTwoModels(1.5) ? backgrounds[0] : backgrounds[1];
}

#pragma region ======================================================================== DEBUG
#if DEBUG_MODE

//void SimulationPrinter::DEBUG_PrintAverageFps()
//{
//    double fps = TimeHelper::Instance().GetFPS();
//    fpsRecord.push_back(fps);
//
//    if (TimeHelper::Instance().GetTime() - lastTimePrintedFps > REFRESH_FPS_EVERY_SECONDS)
//    {
//        shownAverageFps = 0;
//
//        for (double fps : fpsRecord)
//            shownAverageFps += fps;
//        shownAverageFps /= fpsRecord.size();
//
//        fpsRecord.clear();
//        lastTimePrintedFps = TimeHelper::Instance().GetTime();
//    }
//
//    string fpsString = "FPS: " + std::to_string(static_cast<int>(shownAverageFps)) + '\n';
//    InsertInPrintBuffer(fpsString, uiColor);
//}

#endif
#pragma endregion

