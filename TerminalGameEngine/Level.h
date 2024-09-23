#pragma once

#include "ISimulationUpdatingEntity.h"

#include <vector>
#include "Frame.h"

class Level : public ISimulationUpdatingEntity
{
    friend class Simulation;

 //---------------------------------------------------------- Settings
private:
    constexpr static float SECONDS_PLAYER_MUST_WAIT_BEFORE_RESTARTING_PRESSING_ANY_KEY = 1.5;

//---------------------------------------------------------- Fields
private:
    bool hasCalledOnPostGameOverPauseEnded = false;
    double gameOverTime = -1;
    double levelStartedTime = 0;
    bool isTerminated = false;

protected:
    Frame gameEndUIMessage;

//---------------------------------------------------------- Methods
public:
   
    virtual void OnGameOver();
    virtual int GetWorldSizeX() const = 0;
    virtual int GetWorldSizeY() const = 0;
    virtual int GetScreenPadding() const = 0;
    virtual string GetBackgroundFileName() { return ""; }

    double GetLevelTime() const;
    bool IsGameOver() const { return gameOverTime > -1; }
    bool IsTerminated() const { return isTerminated; }

protected:
    virtual double ShowGameOverScreenDelay() const { return 1; }
    virtual void Update() override;
    virtual void OnPostGameOverPauseEnded() { hasCalledOnPostGameOverPauseEnded = true; }
    virtual void LoadInSimulation();

    bool IsPostGameOverPauseEnded() const;
    bool CanPlayerPressKeyToRestartGame() const;
    void Terminate() { isTerminated = true; }

};