#include "LevelEndFlag.h"
#include "Bunny.h"
#include "Level.h"

const Model LevelEndFlag::flagModel//todo reverse model later
{
     {'|',' '},
     {'|','/'},
     {'|','\\'}
};

LevelEndFlag::LevelEndFlag(Level* level, int xPos, int yPos) : GameObject(xPos, yPos), level(level) { }

void LevelEndFlag::OnCollisionEnter(GameObject* other, Direction collisionDir)
{
    if (static_cast<Bunny*>(other) != nullptr)
        level->NotifyGameOver();
}