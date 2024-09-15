#include "ObstaclesLevel.h"

#include "Simulation.h"
#include "ScreenManager.h"
#include "StaticCollider.h"
#include "FileUtils.h"
#include "Persistence.h"
#include "InputUtils.h"
#include "AudioManager.h"
#include "Bunny.h"
#include "ObstaclesSpawner.h"

void ObstaclesLevel::Update()
{
    if (gameOverTime < 0)
        return;

    if (IsShowGameoverDelayExpired() && isShowingGameOverScreen == false)
    {
        int bestScore = Persistence::LoadBestScore(PERSISTENCE_FILE_NAME);
        int score = GetLevelTime();

        if (score > bestScore)
            Persistence::SaveBestScore(PERSISTENCE_FILE_NAME, score);

        if (isShowingGameOverScreen == false)
        {
            //setup gameover message
            string messageEnding = score > bestScore ? "new record!" : ("best: " + std::to_string(bestScore));
            string message = "you survived for " + std::to_string(score) + " seconds, " + messageEnding;
            //centers message
            string leftSpacing = "";
            for (int i = 0; i < (42 - message.size()) / 2; ++i)
                leftSpacing += " ";
            message = leftSpacing + message;

            FileUtils::ReplaceChar(gameEndUIMessage,message,'$');

            Simulation::Instance().GetScreenManager()->SetUIMessage(gameEndUIMessage);
            isShowingGameOverScreen = true;
        }
    }
    else if (CanPlayerPressKeyToRestartGame() && InputUtils::IsAnyKeyPressed())
    {
        Simulation::Instance().Terminate();
    }
}

void ObstaclesLevel::OnGameOver()
{
    if (IsGameOver())
        return;

    Level::OnGameOver();
    AudioManager::Instance().StopMusic();
    AudioManager::Instance().PlayFx("gameover.wav");
}

void ObstaclesLevel::Load()
{
    Level::Load();

    Simulation& simulation = Simulation::Instance();
    simulation.Reset(this, WORLD_SIZE_X, WORLD_SIZE_Y, SCREEN_PADDING, true, BACKGROUND_FILES);

    const ScreenManager* screenManager = simulation.GetScreenManager();

    FileUtils::ReadFrameFromFile
    (
        "gameover-screen.txt", 
        screenManager->GetScreenSizeX(),
        screenManager->GetScreenSizeY(),
        gameEndUIMessage
    );

    //------------------------------- bunny setup
    Bunny* bunny = new Bunny(9, simulation.GetScreenPadding() + 5, this);
    Simulation::Instance().TryAddGameObject(bunny);

    //------------------------------- floor setup
    StaticCollider* floor = new StaticCollider(0, simulation.GetScreenPadding(), simulation.GetWorldSizeX(), 1, ' ');
    simulation.TryAddGameObject(floor);

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
        1,
        2,
        4,
        5,
        6,
        6
    };

    float increaseIntensityEverySeconds = 10;
    float stopSpawningWhenPhaseChangesDuration = 1;

    std::vector<int> ySpawnPoints = { 5,9,13 };

    ObstaclesSpawner* spawner = new ObstaclesSpawner
    (
        spawnerPosX,
        spawnerPosY,
        minSpawnDelays,
        maxSpawnDelays,
        moveSpeeds,
        increaseIntensityEverySeconds,
        stopSpawningWhenPhaseChangesDuration,
        ySpawnPoints
    );

    simulation.TryAddGameObject(spawner);
    AudioManager::Instance().PlayRandomMusic();
}
