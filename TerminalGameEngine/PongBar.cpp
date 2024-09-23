#include "PongBar.h"
#include "InputUtils.h"
#include "Simulation.h"

PongBar::PongBar
(
    int xPos,
    int yPos,
    uint sizeX,
    uint sizeY,
    char modelChar,
    double moveSpeed,
    double deflectBallFactor,
    bool isBottomBar
) :
    VariableSizeCollider(xPos, yPos, sizeX, sizeY, modelChar),
    moveSpeed(moveSpeed),
    deflectBallFactor(deflectBallFactor),
    isBottomBar(isBottomBar) { }

void PongBar::Update()
{
    if (Simulation::Instance().GetActiveLevel()->IsGameOver())
        return;
    
    if ((isBottomBar && InputUtils::IsPressingA()) || !isBottomBar && InputUtils::IsPressingArrowLeft())
        Move(Direction::left, moveSpeed);
    else if ((isBottomBar && InputUtils::IsPressingD()) || (!isBottomBar && InputUtils::IsPressingArrowRight()))
        Move(Direction::right, moveSpeed);
}
