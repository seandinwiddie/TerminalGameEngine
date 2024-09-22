#include "Bunny.h"
#include "Level.h"

const std::vector<std::vector<char>> Bunny::walkLeftModel
{
    {'/',-36, CHEST_CHAR, '_', '|'},
    {'(', EYE_CHAR, NOSE_CHAR, EYE_CHAR, ')'},
    {'(', 92, '(', 92, ' '}
};

const std::vector<std::vector<char>> Bunny::walkRightModel
{
     { '|','_',CHEST_CHAR,-36,92},
     { '(',EYE_CHAR, NOSE_CHAR, EYE_CHAR,')'},
     { ' ','/',')','/',')'}
};

const std::vector<std::vector<char>> Bunny::jumpRightModel
{
    {92,-36,CHEST_CHAR,-36,'/'},
    {'(', EYE_CHAR ,NOSE_CHAR, EYE_CHAR,')'},
    {' ','/',')','/',')'}
};

const std::vector<std::vector<char>> Bunny::jumpLeftModel
{
    {92,-36,CHEST_CHAR,-36,'/'},
    {'(', EYE_CHAR,NOSE_CHAR, EYE_CHAR,')'},
    {'(', 92, '(', 92, ' '}
};

const std::vector<std::vector<char>> Bunny::defeatedModel
{
    {'|',-36,CHEST_CHAR,-36,'|'},
    {'(',GAMEOVER_EYE_CHAR,NOSE_CHAR,GAMEOVER_EYE_CHAR,')'},
    {' ','/',')','/',')'}
};

const std::vector<std::vector<char>> Bunny::idleModelRight
{
    {'|','_',CHEST_CHAR,'_','|'},
    {'(', EYE_CHAR ,NOSE_CHAR, EYE_CHAR,')'},
    {' ','/',')','/',')'}
};

const std::vector<std::vector<char>> Bunny::idleModelLeft
{
    {'|','_',CHEST_CHAR,'_','|'},
    {'(', EYE_CHAR, NOSE_CHAR, EYE_CHAR,')'},
    {'(', 92, '(', 92, ' '}
};

Bunny::Bunny(int xPos, int yPos, Level* level) : CollidingObject(xPos, yPos), level(level)
{
    SetState(State::idle);
    jumpingModel = jumpLeftModel;
    idleModel = idleModelLeft;
    walkingModel = walkLeftModel;
    previousPositionX = GetPosX();
}

void Bunny::Update()
{
    CollidingObject::Update();

    HandleIdleWalkState();

    if (state == State::walking && GetPosX() != previousPositionX)
    {
        previousPositionX = GetPosX();
        bool isTimeForLeftModel = TimeHelper::Instance().IsTimeForFirstOfTwoModels(STEP_ANIM_EVERY_SECONDS);
        jumpingModel = isTimeForLeftModel ? jumpLeftModel : jumpRightModel;
        idleModel = isTimeForLeftModel ? idleModelLeft : idleModelRight;
        walkingModel = isTimeForLeftModel ? walkLeftModel : walkRightModel;
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
        SetModel(defeatedModel);
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
    bool isPressingSpace = InputUtils::IsPressingSpace();

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
    bool isPressingA = InputUtils::IsPressingA();
    bool isPressingD = InputUtils::IsPressingD();

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
        AudioManager::Instance().PlayFx("jump.wav",0.1);
    }
}

float Bunny::GetGravityScale() const
{
    if (state == State::jumpingUp)
        return 0;

    if (InputUtils::IsPressingSpace() && state == State::jumpingDown)
        return MOVE_DOWN_CONTROLLED_SPEED;

    return MOVE_DOWN_SPEED;
}

void Bunny::Move(Direction direction, float moveSpeed)
{
    GameObject::Move(direction, moveSpeed);
    if (direction == Direction::right || direction == Direction::left)
        lastTimeMovedOnX = TimeHelper::Instance().GetTime();
}

void Bunny::OnCollisionEnter(CollidingObject* other, Direction collisionDirection)
{
    if (dynamic_cast<Obstacle*>(other) != nullptr)
    {
        SetState(State::defeated);
        level->OnGameOver();
        return;
    }

    switch (collisionDirection)
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