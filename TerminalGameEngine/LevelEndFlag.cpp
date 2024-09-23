#include "LevelEndFlag.h"
#include "Bunny.h"
#include "Level.h"

const std::vector<std::vector<char>> LevelEndFlag::flagModel
{
     {'|',' '},
     {'|','/'},
     {'|','\\'}
};

LevelEndFlag::LevelEndFlag(Level* level, int xPos, int yPos) : GameObject(xPos, yPos), level(level) { }

void LevelEndFlag::OnCollisionEnter(GameObject* other, Direction collisionDirection)
{
    if (static_cast<Bunny*>(other) != nullptr)
    {
        level->OnGameOver();
    }
}