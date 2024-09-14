#pragma once

#include "ILevel.h";
#include "PuzzleLevel.h"
#include "ObstaclesLevel.h"

namespace MainMenuUtils
{
    static ILevel* ShowLevelSelection()
    {
        std::cout << "Press:" << std::endl << "1 -> play game" << std::endl << "2 -> enter test room" << std::endl;

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