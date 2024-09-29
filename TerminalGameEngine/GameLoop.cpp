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
#include "SpaceInvadersLevel.h"

using namespace std;
using namespace InputUtils;

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
        if (IsKeyPressed(Key::ESC))
            return true;
    }
    return false;
}

Level* GameLoop::ShowLevelSelection()
{
    Terminal::Instance().Clear();

    Terminal::Instance().SetColor(Terminal::CYAN);
    cout << "Terminal Game Engine demos:" << endl << endl;

    Terminal::Instance().SetColor(Terminal::GREEN);
    cout << "1 -> space invaders" << endl;
    Terminal::Instance().SetColor(Terminal::CYAN_DARK);
    cout << "2 -> endless runner" << endl;
    Terminal::Instance().SetColor(Terminal::YELLOW);
    cout << "3 -> puzzle game" << endl;
    Terminal::Instance().SetColor(Terminal::RED);
    cout << "4 -> pong" << endl;

#if DEBUG_MODE
    Terminal::Instance().SetColor(Terminal::WHITE);
    cout << "5 -> collisions test" << endl;
#endif
    
    Terminal::Instance().SetColor(Terminal::CYAN);
    cout << endl
        << "esc -> return to main menu" << endl;

    cout << "music by 'Cody O'Quinn'" << endl;

    while (true)
    {
        if (IsKeyPressed(Key::NUM_1))
        {
            return new SpaceInvadersLevel();
            break;
        }
        else if (IsKeyPressed(Key::NUM_2))
        {
            return new EndlessRunnerLevel();
            break;
        }
        else if (IsKeyPressed(Key::NUM_3))
        {
            return new PuzzleLevel();
            break;
        }
        else if (IsKeyPressed(Key::NUM_4))
        {
            return new PongLevel();
            break;
        }
#if DEBUG_MODE
        else if (IsKeyPressed(Key::NUM_5))
        {
            return new CollisionsTestLevel();
            break;
        }
#endif
    }
}