#include "Bunny.h"
#include "Level.h"
#include "InputUtils.h"
#include "TimeHelper.h"
#include "AudioManager.h"
#include "Obstacle.h"

using namespace InputUtils;

const Model Bunny::MODEL_WALK_LEFT
{
    {'/',-36, CHEST_CHAR, '_', '|'},
    {'(', EYE_CHAR, NOSE_CHAR, EYE_CHAR, ')'},
    {'(', 92, '(', 92, ' '}
};

const Model Bunny::MODEL_WALK_RIGHT
{
     { '|','_',CHEST_CHAR,-36,92},
     { '(',EYE_CHAR, NOSE_CHAR, EYE_CHAR,')'},
     { ' ','/',')','/',')'}
};

const Model Bunny::MODEL_JUMP_RIGHT
{
    {92,-36,CHEST_CHAR,-36,'/'},
    {'(', EYE_CHAR ,NOSE_CHAR, EYE_CHAR,')'},
    {' ','/',')','/',')'}
};

const Model Bunny::MODEL_JUMP_LEFT
{
    {92,-36,CHEST_CHAR,-36,'/'},
    {'(', EYE_CHAR,NOSE_CHAR, EYE_CHAR,')'},
    {'(', 92, '(', 92, ' '}
};

const Model Bunny::MODEL_DEFEATED
{
    {'|',-36,CHEST_CHAR,-36,'|'},
    {'(',GAMEOVER_EYE_CHAR,NOSE_CHAR,GAMEOVER_EYE_CHAR,')'},
    {' ','/',')','/',')'}
};

const Model Bunny::MODEL_IDLE_RIGHT
{
    {'|','_',CHEST_CHAR,'_','|'},
    {'(', EYE_CHAR ,NOSE_CHAR, EYE_CHAR,')'},
    {' ','/',')','/',')'}
};

const Model Bunny::MODEL_IDLE_LEFT
{
    {'|','_',CHEST_CHAR,'_','|'},
    {'(', EYE_CHAR, NOSE_CHAR, EYE_CHAR,')'},
    {'(', 92, '(', 92, ' '}
};

Bunny::Bunny(int xPos, int yPos, Level* level) : GameObject(xPos, yPos), level(level)
{
    SetState(State::idle);
    jumpingModel = MODEL_JUMP_LEFT;
    idleModel = MODEL_IDLE_LEFT;
    walkingModel = MODEL_WALK_LEFT;
    previousPositionX = GetPosX();
}

void Bunny::Update()
{
    GameObject::Update();

    HandleIdleWalkState();

    if (state == State::walking && GetPosX() != previousPositionX)
    {
        previousPositionX = GetPosX();
        bool isTimeForLeftModel = TimeHelper::Instance().IsTimeForFirstOfTwoModels(STEP_ANIM_EVERY_SECONDS);
        jumpingModel = isTimeForLeftModel ? MODEL_JUMP_LEFT : MODEL_JUMP_RIGHT;
        idleModel = isTimeForLeftModel ? MODEL_IDLE_LEFT : MODEL_IDLE_RIGHT;
        walkingModel = isTimeForLeftModel ? MODEL_WALK_LEFT : MODEL_WALK_RIGHT;
    }

    //prevent movement when game is over
    if (level->IsGameOver() == false)
    {
        HandleVerticalMovement();
        HandleHorizontalMovement();
    }

    UpdateModel();
}

void Bunny::UpdateModel()
{
    switch (state)
    {
    case State::defeated:
        SetModel(MODEL_DEFEATED);
        break;

    case State::idle:
        SetModel(idleModel);
        break;

    case State::jumpingUp:
    case State::jumpingDown:
        SetModel(jumpingModel);
        break;

    case State::walking:
        SetModel(walkingModel);
        break;
    }
}

void Bunny::HandleIdleWalkState()
{
    auto debugTime = TimeHelper::Instance().GetTime();
    if (TimeHelper::Instance().GetTime() - lastTimeMovedOnX > 0.2)
    {
        if (state == State::walking)
            SetState(State::idle);
        return;
    }
    else if (state == State::idle)
    {
        SetState(State::walking);
    } 
}

void  Bunny::HandleVerticalMovement()
{
    bool isPressingSpace = IsKeyPressed(Key::SPACE);

    if (isPressingSpace == false && IsTouchingGround() && IsJumping())
        SetState(State::walking);
          
        
    switch (state)
    {
    case State::idle:
    case State::walking:
        if (isPressingSpace)
        {
            jumpStartingY = GetPosY();
            SetState(State::jumpingUp);
        }
        break;

    case State::jumpingUp:
        if (isPressingSpace)
        {
            Move(Direction::up, MOVE_UP_SPEED);
        }
        else
        {
            SetState(State::jumpingDown);
            return;
        }
               

        if (GetPosY() == jumpStartingY + JUMP_HEIGHT)
                SetState(State::jumpingDown);
        break;
    }
}

void Bunny::HandleHorizontalMovement()
{
    bool isPressingA = IsKeyPressed(Key::A);
    bool isPressingD = IsKeyPressed(Key::D);

    if ((isPressingA && isPressingD) || state == State::defeated)
        return;

    if (isPressingA)
        Move(Direction::left, SIDE_MOVEMENT_SPEED);
    if (isPressingD)
        Move(Direction::right, SIDE_MOVEMENT_SPEED);
}

void Bunny::SetState(State newState)
{

    if (state == newState)
        return;

    if (state == State::defeated)
        return;

    HandleSounds(state, newState);

    state = newState;
}

void Bunny::HandleSounds(State oldState, State newState)
{
    if (newState == State::jumpingUp)
    {
        AudioManager::Instance().PlayFx("Platform/jump.wav",0.1);
    }
}

double Bunny::GetGravityScale() const
{
    if (state == State::jumpingUp)
        return 0;

    if (IsKeyPressed(Key::SPACE) && state == State::jumpingDown)
        return MOVE_DOWN_CONTROLLED_SPEED;

    return MOVE_DOWN_SPEED;
}

void Bunny::Move(Direction direction, double moveSpeed)
{
    GameObject::Move(direction, moveSpeed);
    if (direction == Direction::right || direction == Direction::left)
        lastTimeMovedOnX = TimeHelper::Instance().GetTime();
}

void Bunny::OnCollisionEnter(GameObject* other, Direction collisionDir)
{
    if (dynamic_cast<Obstacle*>(other) != nullptr)
    {
        SetState(State::defeated);
        level->NotifyGameOver();
        return;
    }

    switch (collisionDir)
    {
    case Direction::down:
        SetState(State::idle);
        break;
    case Direction::up:
        if (state == State::jumpingUp)
            SetState(State::jumpingDown);
        break;
    }
}