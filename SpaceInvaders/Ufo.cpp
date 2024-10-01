#include "Ufo.h"
#include "RandomUtils.h"
#include "AudioManager.h"

const vector<size_t> Ufo::POSSIBLE_SCORES = { 50,100,150,200,250,300 };

const Model Ufo::MODEL_1 =
{
	{ '/', '(', ')', '\\' },
	{ '\\', '_', '_', '/'}

};

size_t Ufo::GetScore() const
{
	int randomIndex = RandomUtils::GetRandomInt(0, static_cast<int>(POSSIBLE_SCORES.size()-1));
	return POSSIBLE_SCORES[randomIndex];
}

void Ufo::Update()
{
	TryMove(moveDirection, MOVE_SPEED);
}

void Ufo::OnCollisionEnter(Collider* other, Direction collisionDir)
{
	Enemy::OnCollisionEnter(other, collisionDir);
	AudioManager::Instance().PlayFx("Resources/Sounds/SpaceInvaders/UfoDefeated.wav");
}