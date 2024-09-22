#include "SimulationPrinter.h"

#include "GameObject.h"
#include "Simulation.h"
#include "Config.h"
#include "Level.h"
#include "TimeHelper.h"
#include "Terminal.h"

#include <windows.h>
#include <cassert>

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
//void SimulationPrinter::InsertHorizontalMarginLine()
//{
//    string str = "";
//    for (int n = 0; n < screenSizeX + 2; ++n)
//        str += '-';
//    str += '\n';
//    InsertInPrintBuffer(str, screenMarginsColor);
//}
//
//void SimulationPrinter::InsertVerticalMarginChar(bool addEndLine)
//{
//    string str = addEndLine ? "|\n" : "|";
//    InsertInPrintBuffer(str, screenMarginsColor);
//}
//
//void SimulationPrinter::InsertInPrintBuffer(char c, int color)
//{
//    if (color != terminal.GetColor() && c != ' ' && c != '\n')
//    {
//        AddPrintBufferToOperations();
//        terminal.SetColor(color);
//        printOperationBuffer = c;
//    }
//    else
//    {
//        printOperationBuffer += c;
//    }
//}
//
//void SimulationPrinter::InsertInPrintBuffer(string& str, int color)
//{
//    if (str.empty())
//        return;
//
//    if (color != terminal.GetColor())
//    {
//        AddPrintBufferToOperations();
//        terminal.SetColor(color);
//        printOperationBuffer = str;
//    }
//    else
//    {
//        printOperationBuffer += str;
//    }
//}
//
//void SimulationPrinter::AddPrintBufferToOperations()
//{
//    if (!printOperationBuffer.empty())
//    {
//        printOperations.push_back(PrintOperation(printOperationBuffer, terminal.GetColor()));
//        printOperationBuffer.clear();
//    }
//}

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

static int counter = 0;

void SimulationPrinter::PrintObject(GameObject* go)
{
    std::vector<std::vector<char>> model = go->GetModel();
    if (model[0].size() == 0)
        return;

    terminal.SetColor(go->GetColor());

    for (int yScreen = GetScreenPos(go->GetPosY()), yModel = 0; yModel < go->GetModelHeight() && yScreen < screenSizeY; ++yScreen, ++yModel)
    {
        for (int xScreen = GetScreenPos(go->GetPosX()), xModel = 0; xModel < go->GetModelWidth() && xScreen < screenSizeX; ++xScreen, ++xModel)
        {
            char charToPrint = go->GetModel()[yModel][xModel];
            terminal.SetCursorPosition(xScreen, screenSizeY - yScreen);
            std::cout << charToPrint;
        }
    }
}

void SimulationPrinter::Clear(int worldXPos, int worldYPos, uint xSize, uint ySize)
{
    for (int yScreen = GetScreenPos(worldYPos), yModel = 0; yModel < ySize && yScreen < screenSizeY; ++yScreen, ++yModel)
    {
        for (int xScreen = GetScreenPos(worldXPos), xModel = 0; xModel < xSize && xScreen < screenSizeX; ++xScreen, ++xModel)
        {
            char charToPrint = IsBackgroundEnabled() ? GetCurrentBackground().chars[yScreen][xScreen] : ' ';
            terminal.SetCursorPosition(xScreen, screenSizeY - yScreen);
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

