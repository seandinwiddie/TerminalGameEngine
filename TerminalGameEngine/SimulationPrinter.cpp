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
    bool showTimeUI,
    const std::vector<string>& backgroundFileNames 
)
    : 
    screenSizeX(screenSizeX),
    screenSizeY(screenSizeY),
    padding(screenPadding),
    showTimeUI(showTimeUI)
{
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

#if DEBUG_MODE
    DEBUG_PrintAverageFps();
#endif

    if (showTimeUI)
    {
        double runTime = Simulation::Instance().GetActiveLevel()->GetLevelTime();
        TerminalUtils::setTextColor(TerminalUtils::FG_WHITE);
        std::cout<< "TIME: " << static_cast<int>(runTime) << '\n';
    }

    PrintUIMessageOnFrame();

       
    for (int m = screenSizeY - 1; m >= 0; --m)
    {
        for (int n = 0; n < screenSizeX; ++n)
        {
            TerminalUtils::setTextColor(frame.colors[m][n]);
            std::cout << frame.chars[m][n];
        }
        std::cout << std::endl;
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
                frame.colors[y][x] = frameUIMessage.colors[y][x];
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
                frame.colors[m][n] = TerminalUtils::FG_WHITE;
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

        if (static_cast<int>(shownAverageFps) < 0)
            std::cout << "a";

        fpsRecord.clear();
        lastTimePrintedFps = TimeHelper::Instance().GetTime();
    }

    std::cout<< "FPS: " << std::to_string(static_cast<int>(shownAverageFps)) + '\n';
}

#endif
#pragma endregion

