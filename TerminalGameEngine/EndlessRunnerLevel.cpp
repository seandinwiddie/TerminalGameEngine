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

void EndlessRunnerLevel::LoadInSimulation()
{
    Level::LoadInSimulation();
    Simulation& simulation = Simulation::Instance();

    gameEndUIMessage.ReadFrameFromFile("gameover-screen.txt", simulation.GetScreenSizeX(), simulation.GetScreenSizeY());

    //------------------------------- bunny setup
    Bunny* bunny = new Bunny(9, simulation.GetScreenPadding(), this);
    simulation.TryAddEntity(bunny);

    //------------------------------- spawner setup
    int spawnerPosX = GetWorldSizeX() - GetScreenPadding();

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
        -8,
        -16,
        -32,
        -40,
        -48,
        -48
    };

    float increaseIntensityEverySeconds = 10;
    float stopSpawningWhenPhaseChangesDuration = 1;

    std::vector<int> ySpawnPoints = { 4,8,12 };

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

    simulation.TryAddEntity(spawner);
    AudioManager::Instance().PlayRandomMusic();
}

void EndlessRunnerLevel::Update()
{
    Level::Update();
    double runTime = Simulation::Instance().GetActiveLevel()->GetLevelTime();
    string header = "TIME: " + std::to_string(static_cast<int>(runTime));
    Simulation::Instance().SetTerminalHeader(header);
}
