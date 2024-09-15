#pragma once

#include "Level.h";
#include "PuzzleLevel.h"
#include "ObstaclesLevel.h"
#include "InputUtils.h"
#include "ScreenManager.h"

#include <iostream>

using namespace std;

namespace MainMenuUtils
{
    static Level* ShowLevelSelection()
    {
        ScreenManager::ClearScreen();
        cout
            << "Press:" << endl
            << "1 -> play endless runner demo" << endl
            << "2 -> play puzzle game demo" << endl << endl
            << "esc inside levels -> main menu" << endl;

        while (true)
        {
            if (InputUtils::IsPressing1())
            {
                return new ObstaclesLevel();
                break;
            }
            if (InputUtils::IsPressing2())
            {
                return new PuzzleLevel();
                break;
            }
        }
    }
}