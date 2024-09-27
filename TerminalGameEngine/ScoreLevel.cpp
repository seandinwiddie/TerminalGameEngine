#include "ScoreLevel.h"
#include "Persistence.h"
#include "Simulation.h"


void ScoreLevel::OnPostGameOverDelayEnded()
{
    const string persistenceFilePath = GetGameOverWindowPath();
    Level::OnPostGameOverDelayEnded();
    int bestScore = Persistence::LoadBestScore(persistenceFilePath);
    int score = static_cast<int>(GetLevelTime());

    if (score > bestScore)
        Persistence::SaveBestScore(persistenceFilePath, score);

    ShowGameOverScreen(score, bestScore);
}