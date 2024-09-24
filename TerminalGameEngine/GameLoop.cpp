#include "GameLoop.h"
#include "Config.h"
#include "EndlessRunnerLevel.h"
#include "PuzzleLevel.h"
#include "Terminal.h"
#include "CollisionsTestLevel.h"
#include "PongLevel.h"
#include "InputUtils.h"
#include "AudioManager.h"
#include "Simulation.h"

using namespace std;

GameLoop::GameLoop()
{
    bool returnToMainMenu = false;
    while (true)
    {
        AudioManager::Instance().StopMusic();
        Level* level = ShowLevelSelection();
        while (true)
        {
           returnToMainMenu = LoopSimulation(level);
           if (returnToMainMenu)
               break;
        }

        delete(level);
    }
}

bool GameLoop::LoopSimulation(Level* level)
{
    Simulation::Instance().LoadLevel(level);
    while (level->IsTerminated() == false)
    {
        Simulation::Instance().Step();
        if (InputUtils::IsPressingEsc())
            return true;
    }
    return false;
}

Level* GameLoop::ShowLevelSelection()
{
    Terminal::Instance().Clear();
    Terminal::Instance().SetColor(Terminal::WHITE);
    cout << "Press:" << endl
         << "1 -> play endless runner demo" << endl
         << "2 -> play puzzle game demo" << endl
         << "3 -> play pong game demo" << endl
         << "4 -> collisions test" << endl
         << endl
         << "esc (inside levels) -> return to main menu" << endl
         << endl
         << "All music by 'Cody O'Quinn'" << endl;

    while (true)
    {
        if (InputUtils::IsPressing1())
        {
            return new EndlessRunnerLevel();
            break;
        }
        if (InputUtils::IsPressing2())
        {
            return new PuzzleLevel();
            break;
        }
        if (InputUtils::IsPressing3())
        {
            return new PongLevel();
            break;
        }
        if (InputUtils::IsPressing4())
        {
            return new CollisionsTestLevel();
            break;
        }
    }
}