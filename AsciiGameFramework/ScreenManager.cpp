#include "ScreenManager.h"

#include "TransformObject.h"
#include "Simulation.h"
#include "Config.h"
#include "Level.h"
#include "FileUtils.h"
#include "TimeUtils.h"

#include "Windows.h"
#include <cassert>

ScreenManager::ScreenManager(const int worldSizeX, const int worldSizeY, const int padding, bool showLevelTime,const std::vector<string>& backgroundFileNames )
    : 
    screenSizeX(worldSizeX - 2 * padding), 
    screenSizeY(worldSizeY - 2 * padding), 
    padding(padding), 
    showLevelTime(showLevelTime)
{
    UIMessage.clear();
    frame.resize(screenSizeY);

    // Resize each row (inner vector) to have SCREEN_X_DIM columns
    for (int i = 0; i < screenSizeY; ++i)
        frame[i].resize(screenSizeX);
       
    InitBackgrounds(backgroundFileNames);      
    //FileUtils::ReadFrameFromFile("gameover-screen.txt", gameOverScreen);
    Clear();

#if DEBUG_MODE
    fpsRecord.clear();
    fpsRecord.resize(0);
#endif
}

void ScreenManager::Print()
{
    string frameString = "";

#if DEBUG_MODE
    DEBUG_PrintAverageFps(frameString);
#endif

    if (showLevelTime)
    {
        double runTime = Simulation::Instance().GetLevel()->GetLevelTime();
        frameString += "TIME: " + std::to_string(static_cast<int>(runTime)) + '\n';
    }

    InsertUIMessageOverFrame();

    // add frame
    for (int m = screenSizeY - 1; m >= 0; --m)
    {               
        string rowString(frame[m].begin(), frame[m].end());
        frameString += rowString + '\n';
    }

    //clear terminal
    ClearScreen();

    std::cout << frameString;
}

void ScreenManager::InsertUIMessageOverFrame()
{
    if (UIMessage.size() == 0)
        return;

    for (int y = 0; y < screenSizeY; ++y)
        for (int x = 0; x < screenSizeX; ++x)
        {
            unsigned char c = UIMessage[y][x];
            if (c != '#')
                frame[y][x] = c;
        }
}

void ScreenManager::InsertGameObject(TransformObject* go)
{
    std::vector<std::vector<unsigned char>> model = go->GetModel();
    if (model[0].size() == 0)
        return;

    for (int yScreen = go->GetScreenPosY(padding), yModel = 0; yModel < go->GetModelHeight(); ++yScreen, ++yModel)
        for (int xScreen = go->GetScreenPosX(padding), xModel = 0; xModel < go->GetModelWidth(); ++xScreen, ++xModel)
            if (IsInsideScreenX(xScreen) && IsInsideScreenY(yScreen))
            {
                auto a = go->GetModelHeight();
                assert(xModel < go->GetModelWidth() && xModel >= 0);
                assert(yModel < go->GetModelHeight() && yModel >= 0);
                unsigned char charToPrint = go->GetModel()[yModel][xModel];
                if(charToPrint!=' ')
                    frame[yScreen][xScreen] = charToPrint;
            }      
}

void ScreenManager::Clear()
{
    for (int m = 0; m < screenSizeY; ++m)
    {
        for (int n = 0; n < screenSizeX; ++n)
        {
            if (IsBackgroundEnabled())
                frame[m][n] = GetCurrentBackground()[m][n];
            else
                frame[m][n] = ' ';
        }
    }
}

void ScreenManager::InitBackgrounds(const std::vector<string>& backgroundFilesNames)
{
    if (backgroundFilesNames.size() == 0)
    {
        backgrounds.resize(0);
        return;
    }

    backgrounds.resize(backgroundFilesNames.size());

    for (int i = 0; i < backgroundFilesNames.size(); i++)
        FileUtils::ReadFrameFromFile(backgroundFilesNames[i], screenSizeX, screenSizeY, backgrounds[i]);
}

std::vector<std::vector<unsigned char>> ScreenManager::GetCurrentBackground()const
{
    return  TimeUtils::Instance().IsTimeForFirstOfTwoModels(1.5) ? backgrounds[0] : backgrounds[1];
}

void ScreenManager::ClearScreen()
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

void ScreenManager::DEBUG_PrintAverageFps(string& frameString)
{
    double fps = TimeUtils::Instance().GetFPS();
    fpsRecord.push_back(fps);

    if (TimeUtils::Instance().GetTime() - lastTimePrintedFps > REFRESH_FPS_EVERY_SECONDS)
    {
        shownAverageFps = 0;

        for (double fps : fpsRecord)
            shownAverageFps += fps;
        shownAverageFps /= fpsRecord.size();

        if (static_cast<int>(shownAverageFps) < 0)
            cout << "a";

        fpsRecord.clear();
        lastTimePrintedFps = TimeUtils::Instance().GetTime();
    }

    frameString += "FPS: " + to_string(static_cast<int>(shownAverageFps)) + '\n';
}

#endif
#pragma endregion

