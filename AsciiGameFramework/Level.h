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
    constexpr static float SHOW_GAMEOVER_SCREEN_AFTER_SECONDS = 1;
    
protected:
    double gameOverTime = -1;
    double levelStartedTime = 0;
    bool isShowingGameOverScreen = false;
    Frame gameEndUIMessage;

public:
    virtual void OnGameOver();
    virtual void Load();
    double GetLevelTime() const;
    bool IsGameOver() const { return gameOverTime > -1; }

protected:
    virtual void Update()override {}
    bool IsShowGameoverDelayExpired() const;
    bool CanPlayerPressKeyToRestartGame() const;
};