#include "LevelEndFlag.h"
#include "Bunny.h"
#include "Level.h"

const Model LevelEndFlag::flagModel
{
     {'|',' '},
     {'|','/'},
     {'|','\\'}
};

LevelEndFlag::LevelEndFlag(Level* level, int xPos, int yPos) : GameObject(xPos, yPos), level(level) { }

void LevelEndFlag::OnCollisionEnter(uset<GameObject*>collidingObjects, Direction collisionDir)
{
    for(GameObject* item : collidingObjects)
        if (static_cast<Bunny*>(item) != nullptr)
            level->OnGameOver();

}