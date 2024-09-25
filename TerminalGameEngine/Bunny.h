#pragma once
#include "Config.h"
#include "GameObject.h"
#include <string>

class Level;

class Bunny : public GameObject
{
    enum class State
    {
        idle,
        walking,
        jumpingUp,
        jumpingDown,
        defeated
    };
    
//---------------------------------------------------------- Model
private:
    static const char CHAR_NOSE = '.';
    static const char CHAR_EYE = 'O';
    static const char CHAR_GAMEOVER_EYE = '*';
    static const char CHAR_CHEST = ':';

    static const Model MODEL_WALK_LEFT;
    static const Model MODEL_WALK_RIGHT;
    static const Model MODEL_JUMP_RIGHT;
    static const Model MODEL_JUMP_LEFT;
    static const Model MODEL_DEFEATED;
    static const Model MODEL_IDLE_RIGHT;
    static const Model MODEL_IDLE_LEFT;

    Level* level;

//---------------------------------------------------------- Settings

    static const size_t JUMP_HEIGHT = 10;
    static constexpr double MOVE_UP_SPEED = 24;
    static constexpr double MOVE_DOWN_SPEED = 24;
    static constexpr double MOVE_DOWN_CONTROLLED_SPEED = 8;
    static constexpr double SIDE_MOVEMENT_SPEED = 24;
    static constexpr double STEP_ANIM_EVERY_SECONDS = 0.7f;

//---------------------------------------------------------- Fields
    State state;
    double lastTimeMovedOnX = 0;
    int previousPositionX;
    int jumpStartingY = -1;

    Model activeModelJump;
    Model activeModelIdle;
    Model activeModelWalk;
//---------------------------------------------------------- Methods
public:
    Bunny(int xPos, int yPos, Level* level);
   
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override;
    virtual int GetColor() const { return Terminal::GREEN; }

protected:
    void Update() override;
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDir) override;
    virtual void OnCollisionExit(Direction endingCollisionDir) override {}
    virtual void InitModel() { SetModel(MODEL_IDLE_LEFT); }

private:
    bool IsJumping() const { return state == State::jumpingDown || state == State::jumpingUp; }
    void SetState(State newState);
    void UpdateModel();
    void SwitchWalkIdleState();
    void HandleVerticalMovement();
    void HandleHorizontalMovement();
    void HandleSounds(State oldState, State newState);
    bool IsTouchingGround() { return collisions[Direction::down].size() > 0; }
    bool IsJumping() { return state == State::jumpingDown || state == State::jumpingUp; }
    void ActivateLeftModels(bool activate);
    void OnMoveCallback(Direction dir);
};