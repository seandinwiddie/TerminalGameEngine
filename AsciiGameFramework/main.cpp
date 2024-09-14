#include "Config.h"

#include "ILevel.h";
#include "MainMenuUtils.h"


int main()
{
    system("COLOR 0A");

    Simulation& simulation = Simulation::Instance();
    ILevel* level = MainMenuUtils::ShowLevelSelection();
    
    while (true)
    {
        level->Load();
        
        //step simulation until it ends
        while (simulation.HasTerminated() == false)
            simulation.Step();
    }
    return 0;
}