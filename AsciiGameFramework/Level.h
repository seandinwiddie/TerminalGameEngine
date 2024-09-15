#pragma once
#include "SimulationObject.h"
#include <vector>
#include "Frame.h"


class Simulation;

class Level : public SimulationObject
{
    friend class Simulation;

private:
    constexpr static float ALLOW_PRESSING_KEY_TO_RESTART_GAME_AFTER_SECONDS = 1.5;
    constexpr static float SHOW_GAMEOVER_SCREEN_AFTER_SECONDS = 1.5;
    bool isGameOverDelayEnded = false;
    double gameOverTime = -1;
    double levelStartedTime = 0;

protected:
    Frame gameEndUIMessage;

public:
    virtual void OnGameOver();
    virtual void Load();
    double GetLevelTime() const;
    bool IsGameOver() const { return gameOverTime > -1; }

protected:
    virtual void Update()override;
    virtual void OnGameOverDelayEnded() = 0;
    bool IsShowGameoverDelayExpired() const;
    bool CanPlayerPressKeyToRestartGame() const;
};