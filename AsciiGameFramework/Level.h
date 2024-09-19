#pragma once

#include "ISimulationUpdatable.h"
#include <vector>
#include "Frame.h"

class Level : public ISimulationUpdatable
{
    friend class Simulation;

 //---------------------------------------------------------- Settings
private:
    constexpr static float SECONDS_PLAYER_MUST_WAIT_BEFORE_RESTARTING_PRESSING_ANY_KEY = 1.5;

//---------------------------------------------------------- Fields
private:
    bool hasCalledOnGameOverDelayEnded = false;
    double gameOverTime = -1;
    double levelStartedTime = 0;
    bool isTerminated = false;

protected:
    Frame gameEndUIMessage;

//---------------------------------------------------------- Methods
public:
    virtual void Load();
    virtual void OnGameOver();
    double GetLevelTime() const;
    bool IsGameOver() const { return gameOverTime > -1; }
    bool IsTerminated() const { return isTerminated; }

protected:
    virtual double ShowGameOverScreenDelay() const { return 1; }
    virtual void Update() override;
    virtual void OnGameOverDelayEnded() = 0;
    bool IsPostGameOverDelayEnded() const;
    bool CanPlayerPressKeyToRestartGame() const;
    void Terminate() { isTerminated = true; }
};