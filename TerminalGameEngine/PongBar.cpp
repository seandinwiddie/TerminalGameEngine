#include "PongBar.h"
#include "InputUtils.h"

void PongBar::Update()
{
    if (isLeftBar)
    {
        if (InputUtils::IsPressingA())
            Move(Direction::left, moveSpeed);
        else if (InputUtils::IsPressingD())
            Move(Direction::right, moveSpeed);
    }
    else
    {
        if (InputUtils::IsPressingArrowLeft())
            Move(Direction::left, moveSpeed);
        else if (InputUtils::IsPressingArrowRight())
            Move(Direction::right, moveSpeed);
    }
}
