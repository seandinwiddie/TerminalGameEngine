#include "LevelEndFlag.h"
#include "Bunny.h"
#include "Level.h"

const Model LevelEndFlag::flagModel
(
    2,
    {
        '|','\\',
        '|','/',
        '|',' ' 
    }
);

LevelEndFlag::LevelEndFlag(Level* level, int xPos, int yPos) : Collider(xPos, yPos), level(level) { }

void LevelEndFlag::OnCollisionEnter(Collider* other, Direction collisionDir)
{
    if (static_cast<Bunny*>(other) != nullptr)
        OnTouchBunny.Notify();
}