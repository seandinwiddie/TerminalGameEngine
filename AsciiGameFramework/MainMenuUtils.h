#pragma once

#include "Level.h";
#include "PuzzleLevel.h"
#include "ObstaclesLevel.h"
#include "InputUtils.h"

#include <iostream>

namespace MainMenuUtils
{
    static Level* ShowLevelSelection()
    {
        std::cout << "Press:" << std::endl << "1 -> play endless runner demo" << std::endl << "2 -> play puzzle game demo" << std::endl;

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