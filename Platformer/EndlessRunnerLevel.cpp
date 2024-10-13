#include "EndlessRunnerLevel.h"
#include "Simulation.h"
#include "StaticCollider.h"
#include "Persistence.h"
#include "InputUtils.h"
#include "AudioManager.h"
#include "Bunny.h"
#include "ObstaclesSpawner.h"
#include "SimulationPrinter.h"
#include "UIPrinter.h"
#include "Frame.h"
#include "RandomUtils.h"

using WindowPosition = UIPrinter::WindowPosition;

const std::array<const char*, EndlessRunnerLevel::MUSIC_FILES_COUNT> EndlessRunnerLevel::MUSIC_FILES =
{
    "Resources/Music/1.wav",
    "Resources/Music/2.wav",
    "Resources/Music/3.wav"
};

void EndlessRunnerLevel::OnPostGameOverDelayEnded()
{
    Level::OnPostGameOverDelayEnded();
    int score = static_cast<int>(GetLevelTime());

    int savedBestScore = Persistence::LoadBestScore(GetPersistenceFilePath());
    if (score > savedBestScore)
        Persistence::SaveBestScore(GetPersistenceFilePath(), score);

    ShowGameOverScreen(score, savedBestScore);
    AudioManager::Instance().PlayFx("Resources/Sounds/Platform/ShowEndScreen.wav");
}

void EndlessRunnerLevel::ShowGameOverScreen(int score, int bestScore)
{
    //setup gameover message
    string messageEnding = score > bestScore ? "new record!" : ("best: " + std::to_string(bestScore));
    string message = "you survived for " + std::to_string(score) + " seconds, " + messageEnding;

    //center message
    string leftSpacing = "";
    for (int i = 0; i < (42 - message.size()) / 2; ++i)
        leftSpacing += " ";
    message = leftSpacing + message;

    gameOverWindow.WriteString(message, '$');

    Simulation::Instance().GetUIPrinter().PrintWindow(gameOverWindow, Terminal::WHITE, WindowPosition::CenterX_TopY);
}

void EndlessRunnerLevel::OnGameOver()
{
    if (IsGameOver())
        return;

    Level::OnGameOver();
    AudioManager::Instance().StopMusic();
    AudioManager::Instance().PlayFx("Resources/Sounds/Platform/GameOver.wav");
}

void EndlessRunnerLevel::LoadInSimulation()
{
    Level::LoadInSimulation();
    Simulation& simulation = Simulation::Instance();

    //----------------- bunny setup
    int bunnyStartingY = static_cast<int>(simulation.GetScreenPadding());
    Bunny* bunny = new Bunny(9, bunnyStartingY);
    bunny->OnObstacleHit.Subscribe([this]() { OnGameOver(); });
    simulation.TryAddEntity(bunny);

    //----------------- obstacles spawner setup
    int spawnerPosX = GetWorldSizeX() - GetScreenPadding();

    std::vector<double> minSpawnDelays
    {
        0.9,
        0.4,
        0.28,
        0.25,
        0.22,
        0.22
    };
    std::vector<double> maxSpawnDelays
    {
        1,
        0.6,
        0.43,
        0.4,
        0.32,
        0.22
    };
    std::vector<double> moveSpeeds
    {
        -8,
        -16,
        -32,
        -40,
        -48,
        -48
    };

    double increaseIntensityEverySeconds = 10;
    double stopSpawningWhenPhaseChangesDuration = 1;

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

    PlayRandomMusic();
}

void EndlessRunnerLevel::PlayRandomMusic()
{
    const char* randomMusic = MUSIC_FILES[RandomUtils::GetRandomInt(0, static_cast<int>(MUSIC_FILES.size() - 1))];
    AudioManager::Instance().PlayMusic(randomMusic);
}

void EndlessRunnerLevel::Update()
{
    Level::Update();
    double runTime = Simulation::Instance().GetActiveLevel()->GetLevelTime();
    int newTime = static_cast<int>(runTime);
    if (shownTime != newTime)
    {
        string header = "TIME: " + std::to_string(newTime);
        Simulation::Instance().GetUIPrinter().PrintOnHeader(header, 0, Terminal::WHITE);
        shownTime = newTime;
    }
}
