#include "SimulationPrinter.h"

#include "TransformObject.h"
#include "Simulation.h"
#include "Config.h"
#include "Level.h"
#include "TimeHelper.h"

#include "Windows.h"
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

void SimulationPrinter::ShowFrameInTerminal()
{
    string frameString = "";

#if DEBUG_MODE
    DEBUG_PrintAverageFps(frameString);
#endif

    if (showTimeUI)
    {
        double runTime = Simulation::Instance().GetActiveLevel()->GetLevelTime();
        frameString += "TIME: " + std::to_string(static_cast<int>(runTime)) + '\n';
    }

    PrintUIMessageOnFrame();

    // add frame
    for (int m = screenSizeY - 1; m >= 0; --m)
    {               
        string rowString(frame.chars[m].begin(), frame.chars[m].end());
        frameString += rowString + '\n';
    }

    ClearTerminal();

    std::cout << frameString;
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
                frame.chars[y][x] = c;
        }
}

void SimulationPrinter::PrintObjectOnFrame(TransformObject* go)
{
    std::vector<std::vector<char>> model = go->GetModel();
    if (model[0].size() == 0)
        return;

    for (int yScreen = go->GetScreenPosY(padding), yModel = 0; yModel < go->GetModelHeight(); ++yScreen, ++yModel)
        for (int xScreen = go->GetScreenPosX(padding), xModel = 0; xModel < go->GetModelWidth(); ++xScreen, ++xModel)
        {
            if (yScreen < screenSizeY && xScreen < screenSizeX)
            {
                char charToPrint = go->GetModel()[yModel][xModel];
                if (charToPrint != ' ')
                    frame.chars[yScreen][xScreen] = charToPrint;
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
                frame.chars[m][n] = GetCurrentBackground().chars[m][n];
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

void SimulationPrinter::ClearTerminal()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };  // Top left corner
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the console screen buffer info
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with spaces
    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coord, &cCharsWritten);

    // Fill the entire screen with the current attributes
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coord, &cCharsWritten);

    // Move the cursor back to the top-left corner
    SetConsoleCursorPosition(hConsole, coord);
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

        if (static_cast<int>(shownAverageFps) < 0)
            std::cout << "a";

        fpsRecord.clear();
        lastTimePrintedFps = TimeHelper::Instance().GetTime();
    }

    frameString += "FPS: " + std::to_string(static_cast<int>(shownAverageFps)) + '\n';
}

#endif
#pragma endregion

