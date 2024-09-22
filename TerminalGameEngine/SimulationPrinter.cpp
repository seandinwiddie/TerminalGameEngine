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
    frame.ResizeY(screenSizeY);
    frame.ResizeX(screenSizeX);
       
    InitBackgrounds(backgroundFileNames);      
    //FileUtils::ReadFrameFromFile("gameover-screen.txt", gameOverScreen);
    ClearFrame();

#if DEBUG_MODE
    fpsRecord.clear();
    fpsRecord.resize(0);
#endif
}

void SimulationPrinter::PrintFrameOnTerminal()
{
#if DEBUG_MODE
    DEBUG_PrintAverageFps();
#endif

    string headerNewLine = header + '\n';
    InsertInPrintBuffer(headerNewLine, uiColor);

    PrintUIMessageOnFrame();

    InsertHorizontalMarginLine();

    //print frame
    for (int m = screenSizeY - 1; m >= 0; --m)
    {
        InsertVerticalMarginChar(false);
        string lineStr = "";
        for (int n = 0; n < screenSizeX; ++n)
        {
            int cellColor = frame.colors[m][n];
            char cellChar = frame.chars[m][n];
            InsertInPrintBuffer(cellChar, cellColor);
        }
        InsertVerticalMarginChar(true);
    }

    InsertHorizontalMarginLine();

    AddPrintBufferToOperations();
    terminal.Clear();
    for (PrintOperation operation : printOperations)
    {
        terminal.SetColor(operation.color);
        std::cout << operation.str;
    }
    printOperations.clear();
}

void SimulationPrinter::InsertHorizontalMarginLine()
{
    string str = "";
    for (int n = 0; n < screenSizeX + 2; ++n)
        str += '-';
    str += '\n';
    InsertInPrintBuffer(str, screenMarginsColor);
}

void SimulationPrinter::InsertVerticalMarginChar(bool addEndLine)
{
    string str = addEndLine ? "|\n" : "|";
    InsertInPrintBuffer(str, screenMarginsColor);
}

void SimulationPrinter::InsertInPrintBuffer(char c, int color)
{
    if (color != terminal.GetColor() && c != ' ' && c != '\n')
    {
        AddPrintBufferToOperations();
        terminal.SetColor(color);
        printOperationBuffer = c;
    }
    else
    {
        printOperationBuffer += c;
    }
}

void SimulationPrinter::InsertInPrintBuffer(string& str, int color)
{
    if (str.empty())
        return;

    if (color != terminal.GetColor())
    {
        AddPrintBufferToOperations();
        terminal.SetColor(color);
        printOperationBuffer = str;
    }
    else
    {
        printOperationBuffer += str;
    }
}

void SimulationPrinter::AddPrintBufferToOperations()
{
    if (!printOperationBuffer.empty())
    {
        printOperations.push_back(PrintOperation(printOperationBuffer, terminal.GetColor()));
        printOperationBuffer.clear();
    }
}

void SimulationPrinter::PrintUIMessageOnFrame()
{
    if (frameUIMessage.GetSizeY() == 0)
        return;

    for (int y = 0; y < screenSizeY; ++y)
        for (int x = 0; x < screenSizeX; ++x)
        {
            char c = frameUIMessage.chars[y][x];
            if (c != UI_MESSAGE_FRAME_IGNORED_CHAR)
            {
                frame.chars[y][x] = c;
                frame.colors[y][x] = uiColor;

                //message color could be customized
                //frame.colors[y][x] = frameUIMessage.colors[y][x];
            }
        }
}

void SimulationPrinter::PrintObjectOnFrame(GameObject* go)
{
    std::vector<std::vector<char>> model = go->GetModel();
    if (model[0].size() == 0)
        return;

    for (int yScreen = go->GetScreenPosY(padding), yModel = 0; yModel < go->GetModelHeight(); ++yScreen, ++yModel)
    {
        for (int xScreen = go->GetScreenPosX(padding), xModel = 0; xModel < go->GetModelWidth(); ++xScreen, ++xModel)
        {
            if (yScreen < screenSizeY && xScreen < screenSizeX)
            {
                char charToPrint = go->GetModel()[yModel][xModel];
                if (charToPrint != ' ')
                {
                    frame.chars[yScreen][xScreen] = charToPrint;
                    frame.colors[yScreen][xScreen] = go->GetColor();
                }

            }
        }
    }
        
}

void SimulationPrinter::ClearFrame()
{
    for (int m = 0; m < screenSizeY; ++m)
    {
        for (int n = 0; n < screenSizeX; ++n)
        {
            if (IsBackgroundEnabled())
            {
                frame.chars[m][n] = GetCurrentBackground().chars[m][n];
                frame.colors[m][n] = backgroundColor;
            }
                
            else
                frame.chars[m][n] = ' ';
        }
    }
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
    InsertInPrintBuffer(fpsString, uiColor);
}

#endif
#pragma endregion

