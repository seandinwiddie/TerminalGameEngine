#include "PongBar.h"
#include "InputUtils.h"
#include "Simulation.h"

using namespace InputUtils;

PongBar::PongBar
(
    int xPos,
    int yPos,
    size_t sizeX,
    size_t sizeY,
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
    
    if ((isBottomBar && IsKeyPressed(Key::A)) || !isBottomBar && IsKeyPressed(Key::ARROW_LEFT))
        TryMove(Direction::left, moveSpeed);
    else if ((isBottomBar && IsKeyPressed(Key::D)) || (!isBottomBar && IsKeyPressed(Key::ARROW_RIGHT)))
        TryMove(Direction::right, moveSpeed);
}
