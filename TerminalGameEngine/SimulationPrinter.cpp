#include "SimulationPrinter.h"

#include "GameObject.h"
#include "Simulation.h"
#include "Config.h"
#include "Level.h"
#include "TimeHelper.h"
#include "TerminalUtils.h"

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
    TerminalUtils::ClearTerminal();

    string toPrintBuffer;
    int currentColor = TerminalUtils::WHITE;
    TerminalUtils::SetColor(currentColor);

#if DEBUG_MODE
    DEBUG_PrintAverageFps(toPrintBuffer);
#endif

    if (header != "")
        toPrintBuffer += header + '\n';

    PrintUIMessageOnFrame();

    //print frame
    for (int m = screenSizeY - 1; m >= 0; --m)
    {
        for (int n = 0; n < screenSizeX; ++n)
        {
            int cellColor = frame.colors[m][n];
            char cellChar = frame.chars[m][n];

            //print buffer if color changed (ignore empty spaces)
            if (cellColor != currentColor && cellChar != ' ' && cellChar != '\n')
            {
                if (!toPrintBuffer.empty())
                {
                    std::cout << toPrintBuffer;
                    toPrintBuffer.clear();
                }
                TerminalUtils::SetColor(cellColor);
                currentColor = cellColor;
            }
            toPrintBuffer += cellChar;
        }
        toPrintBuffer += '\n';
    }

    if (!toPrintBuffer.empty())
    {
        std::cout << toPrintBuffer;
        toPrintBuffer.clear();
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
                frame.colors[y][x] = UI_COLOR;

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
                frame.colors[m][n] = BACKGROUND_COLOR;
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

void SimulationPrinter::DEBUG_PrintAverageFps(string& frameString)
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

    frameString += "FPS: " + std::to_string(static_cast<int>(shownAverageFps)) + '\n';
}

#endif
#pragma endregion

