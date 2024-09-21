#include "EndlessRunnerLevel.h"

#include "Simulation.h"
#include "SimulationPrinter.h"
#include "StaticCollider.h"
#include "Persistence.h"
#include "InputUtils.h"
#include "AudioManager.h"
#include "Bunny.h"
#include "ObstaclesSpawner.h"
#include "Frame.h"

void EndlessRunnerLevel::OnGameOverDelayEnded()
{
    int bestScore = Persistence::LoadBestScore(PERSISTENCE_FILE_NAME);
    int score = GetLevelTime();

    if (score > bestScore)
        Persistence::SaveBestScore(PERSISTENCE_FILE_NAME, score);

    ShowGameOverScreen(score, bestScore);
    AudioManager::Instance().PlayFx("show-end-screen.wav");
}

void EndlessRunnerLevel::ShowGameOverScreen(int score, int bestScore)
{
    //setup gameover message
    string messageEnding = score > bestScore ? "new record!" : ("best: " + std::to_string(bestScore));
    string message = "you survived for " + std::to_string(score) + " seconds, " + messageEnding;
    //centers message
    string leftSpacing = "";
    for (int i = 0; i < (42 - message.size()) / 2; ++i)
        leftSpacing += " ";
    message = leftSpacing + message;

    gameEndUIMessage.ReplaceChar(message, '$');

    Simulation::Instance().ShowUIFrame(gameEndUIMessage);
}

void EndlessRunnerLevel::OnGameOver()
{
    if (IsGameOver())
        return;

    Level::OnGameOver();
    AudioManager::Instance().StopMusic();
    AudioManager::Instance().PlayFx("gameover.wav");
}

void EndlessRunnerLevel::Load()
{
    Level::Load();

    Simulation& simulation = Simulation::Instance();
    simulation.Reset(this, WORLD_SIZE_X, WORLD_SIZE_Y, SCREEN_PADDING, true, BACKGROUND_FILES);

    gameEndUIMessage.ReadFrameFromFile("gameover-screen.txt", simulation.GetScreenSizeX(), simulation.GetScreenSizeY());

    //------------------------------- bunny setup
    Bunny* bunny = new Bunny(9, simulation.GetScreenPadding() + 5, this);
    Simulation::Instance().TryAddObject(bunny);

    //------------------------------- floor setup
    StaticCollider* floor = new StaticCollider(0, simulation.GetScreenPadding(), simulation.GetWorldSizeX(), 1, ' ');
    simulation.TryAddObject(floor);

    //------------------------------- spawner setup
    int spawnerPosX = WORLD_SIZE_X - SCREEN_PADDING;
    int spawnerPosY = SCREEN_PADDING + 1;

    std::vector<float> minSpawnDelays
    {
        0.9,
        0.4,
        0.28,
        0.25,
        0.22,
        0.22
    };
    std::vector<float> maxSpawnDelays
    {
        1,
        0.6,
        0.43,
        0.4,
        0.32,
        0.22
    };
    std::vector<float> moveSpeeds
    {
        -1,
        -2,
        -4,
        -5,
        -6,
        -6
    };

    float increaseIntensityEverySeconds = 10;
    float stopSpawningWhenPhaseChangesDuration = 1;

    std::vector<int> ySpawnPoints = { 5,9,13 };

    ObstaclesSpawner* spawner = new ObstaclesSpawner
    (
        spawnerPosX,
        minSpawnDelays,
        maxSpawnDelays,
        moveSpeeds,
        ySpawnPoints,
        increaseIntensityEverySeconds,
        stopSpawningWhenPhaseChangesDuration
    );

    simulation.AddUpdatable(spawner);
    AudioManager::Instance().PlayRandomMusic();
}
