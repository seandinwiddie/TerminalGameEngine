#include "Obstacle.h"
#include "AudioManager.h"
#include "TimeHelper.h"


Model Obstacle::model = {};

void Obstacle::OnCollisionEnter(GameObject* other, Direction collisionDir)
{
    AudioManager::Instance().PlayFx("Platform/hit.wav", 0.2);
}

void Obstacle::InitModel()
{
    if (model.size() == 0)
        model = CreteModelUsingChar(-37, size_t(4), size_t(2));
    SetModel(model);
}