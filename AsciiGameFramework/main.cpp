#include "Config.h"

#include "Level.h";
#include "MainMenuUtils.h"
#include "Simulation.h"


int main()
{
    system("COLOR 0A");

    Simulation& simulation = Simulation::Instance();
    Level* level = MainMenuUtils::ShowLevelSelection();
    
    while (true)
    {
        level->Load();
        
        //step simulation until it ends
        while (simulation.HasTerminated() == false)
            simulation.Step();
    }
    return 0;
}